import React, { useEffect, useMemo, useState } from 'react'
import { createEditor, Descendant } from 'slate'
import { Slate, Editable, withReact } from 'slate-react'
import { withHistory, } from 'slate-history'
import './Editor2.css';
import Switch from "react-switch";
import { TokensData } from './TokensPreData';

const Editor2 = () => 
{
    const [CompiledErros,setCompiledErros] = useState([])
    const [CompiledWarnings,setCompiledWarnings] = useState([])
    const [updateHelper,setupdateHelper] = useState(false)
    const [WholeTXT,setWholeTXT] = useState('')
    const [checked,setChecked] = useState(false)
    const editor = useMemo(() => withHistory(withReact(createEditor())),[])  

    useEffect(()=>
    {      
        if(CompiledErros.length || CompiledWarnings.length)
        {
            console.log(CompiledErros)
            console.log(CompiledWarnings)
            setCompiledErros([])
            setCompiledWarnings([])
           
        }
        
    },[updateHelper])

    function isNumber (value) 
    {
        if(parseInt(value) || parseInt(value)===0)
        {
            return true
        }

        return false
    }

    function copyTokenData()
    {
        const TokensDataCpy = []

        for(let i = 0; i<TokensData.length; i++)
        {
            TokensDataCpy.push(
            {
                hasSomething:TokensData[i].hasSomething,
                TokenName: TokensData[i].TokenName,
                cutSequence:TokensData[i].cutSequence,
                typeofdata:TokensData[i].typeofdata,
                maxamountcharacters:TokensData[i].maxamountcharacters,
            })
        }
        return TokensDataCpy
    }

    function analyzSpaces ()
    {     
        let line = 1 //linha inicial
        let column = 1 //coluna inicial

        for(let index = 0; index < WholeTXT.length; index++,column++)
        {
            if(WholeTXT[index] === '\n') //caso tenha um ENTER 
            {
                line++ //adiciona mais uma linha
                column = 1 //reseta as colunas
            }
            
            //caso tenha 2 espacoes em sequencia com um texto entre eles salvar erro
            if(WholeTXT[index] === ' ' && WholeTXT[index + 1] === ' ' && WholeTXT[WholeTXT.length - 1] !== ' ') 
            {
                setCompiledErros((prevstate)=>
                {
                    prevstate.push(
                    {
                        linha:line,//linha do erro
                        coluna:column,//coluna do erro
                        erro:`Mais de um espaco entre as palavras`,//erro em si 
                    })
                    return prevstate
                })

                console.log("Espaco mais de uma vez, ERRO")
            }
        }
    } 

    function analyzToken()
    {
        //console.log('TokensData',TokensData)
        let erros = []
        let warnings = []
        let token = ''

        const TokensDataCpy = copyTokenData()

        let TokenIndex = 0
        let line = 1 //linha inicial
        let lineprevState = 1 //linha inicial
        let column = 1 //coluna inicial
        let columnprevState = 1 //coluna inicial
        let tokensOK = 0

        
       // console.log('TokenIndex',TokenIndex)
        //console.log('lineprevState',lineprevState)
        //console.log('line',line)
       // console.log('column',column)
       // console.log('tokensOK',tokensOK)
        
        //iterando todo o texto
        for(let index = 0, cutindex = 0; index < WholeTXT.length; index++,column++)
        {
            if(WholeTXT[index] === '\n') //caso tenha um ENTER 
            {         
                //console.log('adding line and reseting column runs')
                line++ //adiciona mais uma linha
                column = 1 //reseta as colunas
                //console.log('column',column)
            }

            if(WholeTXT[index] === TokensDataCpy[TokenIndex].cutSequence[cutindex]) 
            {
                if(cutindex === TokensDataCpy[TokenIndex].cutSequence.length - 1)
                {
                    //console.log(`Token ${TokensDataCpy[TokenIndex].TokenName} CUTPOINT found`)
                    console.log(token)
                    if(TokensDataCpy[TokenIndex].hasSomething) 
                    {
                        if((TokensDataCpy[TokenIndex].maxamountcharacters > 0) && (token.length > TokensDataCpy[TokenIndex].maxamountcharacters))
                        {                    
                            warnings.push(
                            {
                                linha:lineprevState,//linha do erro
                                coluna:columnprevState,//coluna do warning
                                warning:`Token ${TokensDataCpy[TokenIndex].TokenName} contem mais caracteres doque o recomendado`,//erro em si 
                            })
                        }
                                              
                        if(TokensDataCpy[TokenIndex].typeofdata !== 'string&number')
                        {
                            for(let i = 0 ;i < token.length; i++)
                            {
                                if(TokensDataCpy[TokenIndex].typeofdata === 'string')
                                {
                                    if(isNumber(token[i]))
                                    {
                                        warnings.push(
                                        {
                                            linha:lineprevState,//linha do erro
                                            coluna:columnprevState,//coluna do warning
                                            warning:`Token ${TokensDataCpy[TokenIndex].TokenName} nao contem so letras`,//erro em si 
                                        })
                                        break
                                    }
                                }
                                else if (TokensDataCpy[TokenIndex].typeofdata === 'number')
                                {
                                    if(!isNumber(token[i]))
                                    {
                                        warnings.push(
                                        {
                                            linha:lineprevState,//linha do erro
                                            coluna:columnprevState,//coluna do warning
                                            warning:`Token ${TokensDataCpy[TokenIndex].TokenName} nao contem so numeros`,//erro em si 
                                        })
                                        break
                                    }
                                }
                            }
                        }   
                        
                        //console.log(`Token ${TokensDataCpy[TokenIndex].TokenName} found`)
                        token = ''
                        tokensOK++
                    }
                    else 
                    {         
                        //console.log('erros pushing')
 
                        erros.push(
                        {
                            linha:lineprevState,//linha do erro
                            coluna:columnprevState ,//coluna do erro
                            erro:`Token ${TokensDataCpy[TokenIndex].TokenName} vazio`,//erro em si 
                        })
                    }

                    //console.log(`Go Analisys next token`)
                    columnprevState = column
                    lineprevState = line
                    TokenIndex++
                    cutindex = 0 
                }
                else cutindex++                
            }
            else 
            {
                if(WholeTXT[index]!== ' ' && WholeTXT[index]!== '\n') 
                {
                    token = token+WholeTXT[index]
                    //console.log(token)

                    if(!TokensDataCpy[TokenIndex].hasSomething)
                    {
                        TokensDataCpy[TokenIndex].hasSomething = true
                        //console.log(`TokenName ${TokensDataCpy[TokenIndex].TokenName} hasSomething`)
                    }                  
                }
                cutindex = 0
            }
        }     
       
        if(tokensOK!=TokensData.length)
        {
            //console.log('Missing tokens')
            //alert here
        }

        setCompiledErros(erros)
        setCompiledWarnings(warnings)
    }

    function Compile (value)
    {
        //console.log(WholeTXT)
        
        analyzSpaces()

        analyzToken()  
        
        setupdateHelper(!updateHelper)
        
    }

    return (
    <div className='center'>
        <div style={{
            display:'flex',
            flexDirection:'row',
            alignItems:'center',
            justifyContent:'flex-end'
            }}>
                <p style={{color:'#d3d3d3' ,marginRight:'1rem'}}>Ultra easy mode</p>

                <Switch
                onChange={()=>
                {
                    console.log("Switched")
                    setChecked(!checked)
                }}
                checked={checked}
                id="normal-switch"
                />
              
        </div>
        
        <div className='EditorContainer'>
            <Slate editor={editor} value={initialText} onChange={(value)=>
            { 
                setWholeTXT(()=>
                {
                    let txt = ''
                    for(let i = 0; i < value.length ; i++)
                    {
                        txt += value[i].children[0].text
                        if((i + 1) !== value.length) txt += '\n'
                    }
                    return txt
                })   

                //CheckTXT(value)
            }}>
                <Editable 
                className='textContainer'
                placeholder="Digite aqui..."                
                />
            </Slate>
        </div>    

        <button style={
        {
            boxShadow: '0.0rem 0.0rem 1.5rem',
            marginTop:'1rem',
            width:'7rem',
            height:'3.5rem',
            borderRadius:'20rem',
            backgroundColor:'#d3d3d3',
            color:'#181818'
        }} 
        onClick={()=>
        {
            Compile()
            //console.log("ButtonClick")
            
        }}>
            Compilar
        </button>
      
    </div>
    )
}

const initialText = 
[
  { 
    type: 'paragraph',
    children: 
    [
        { text: '' },
    ],
  },
]


export default Editor2