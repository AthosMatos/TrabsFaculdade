import React, { useEffect, useMemo, useState } from 'react'
import { createEditor, Descendant } from 'slate'
import { Slate, Editable, withReact } from 'slate-react'
import { withHistory, } from 'slate-history'
import './Editor2.css';
import Switch from "react-switch";
import { TokensData } from './TokensPreData';

const Editor2 = () => 
{
    const [analyzsDone,setAnalyzsDone] = useState(false)
    const [erros,seterros] = useState([])
    const [WholeTXT,setWholeTXT] = useState('')
    const [checked,setChecked] = useState(false)
    const editor = useMemo(() => withHistory(withReact(createEditor())),[])  

    useEffect(()=>
    {        
        //console.log(analyzsDone)
        console.log(erros)
        seterros([])
        
    },[analyzsDone])

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
                seterros((prevstate)=>
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

        const TokensDataCpy = copyTokenData()

        let TokenIndex = 0
        let lineprevState = 1 //linha inicial
        let line = 1 //linha inicial
        let column = 1 //coluna inicial
        let tokensOK = 0

        //iterando todo o texto
        for(let index = 0, cutindex = 0; index < WholeTXT.length; index++,column++)
        {
            if(WholeTXT[index] === '\n') //caso tenha um ENTER 
            {
                line++ //adiciona mais uma linha
                column = 1 //reseta as colunas
            }

            if(WholeTXT[index] === TokensDataCpy[TokenIndex].cutSequence[cutindex]) 
            {
                if(cutindex === TokensDataCpy[TokenIndex].cutSequence.length - 1)
                {
                    console.log(`Token ${TokensDataCpy[TokenIndex].TokenName} CUTPOINT found`)

                    if(TokensDataCpy[TokenIndex].hasSomething) 
                    {
                        console.log(`Token ${TokensDataCpy[TokenIndex].TokenName} found`)
                        tokensOK++
                    }
                    else 
                    {
                        console.log(`Token ${TokensDataCpy[TokenIndex].TokenName} NOT found`)
                        seterros((prevstate)=>
                        {
                            prevstate.push(
                            {
                                linha:lineprevState,//linha do erro
                                coluna:column - TokensDataCpy[TokenIndex].cutSequence.length,//coluna do erro
                                erro:`Token ${TokensDataCpy[TokenIndex].TokenName} vazio`,//erro em si 
                            })
                            return prevstate
                        })
                    }

                    console.log(`Go Analisys next token`)

                    lineprevState = line
                    TokenIndex++
                    cutindex = 0 
                }
                else cutindex++                
            }
            else 
            {
                if(WholeTXT[index]!== ' ' && WholeTXT[index]!== '\n') TokensDataCpy[TokenIndex].hasSomething = true
                cutindex = 0
            }
           
        }       
    }

    function Compile (value)
    {
        //console.log(WholeTXT)
        
        analyzSpaces()

        analyzToken()

        setAnalyzsDone(!analyzsDone)

      
        
    }

    return (
    <div className='center'>
        <div style={{
            display:'flex',
            flexDirection:'row',
            alignItems:'center',
            justifyContent:'flex-end'
            }}>
                <p style={{marginRight:'1rem'}}>Ultra easy mode</p>

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
            backgroundColor:'#181818',
            color:'#d3d3d3'
        }} 
        onClick={()=>
        {
            //console.log("ButtonClick")
            Compile()
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