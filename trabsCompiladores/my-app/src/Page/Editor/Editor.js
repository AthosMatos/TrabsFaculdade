import React, { useEffect, useMemo, useState } from 'react'
import { createEditor, Descendant } from 'slate'
import { Slate, Editable, withReact } from 'slate-react'
import { withHistory, } from 'slate-history'
import './Editor.css';

const Editor = () => 
{
    const [line,setLine] = useState()
    const [CurrentToken,setCurrentToken] = useState('')
    const [PrevTokens,setPrevTokens] = useState([])
    const [TokenID,setTokenID] = useState('instituicao')
    const [TokenIndex,setTokenIndex] = useState()
    const [warning,setWarning] = useState()
    const [lineIndex,setlineIndex] = useState(0)
    const editor = useMemo(() => withHistory(withReact(createEditor())),[])

    const isNumber = (key) =>
    {
        if(parseInt(key) || parseInt(key)===0)
        {
            return true
        }

        return false
    }

    const analyzSpaces = (value) =>
    {     
        for(let index = 0; index < value.length; index++)
        {
            let CurrentLine = value[index].children[0].text

            for(let i = 0; i<CurrentLine.length - 1; i++)
            {   
                if(CurrentLine[i] === ' ' && CurrentLine[i + 1] === ' ' && CurrentLine[CurrentLine.length - 1] !== ' ') 
                {
                    setWarning("Mais de um espaco entre as palavras")
                    console.log("Espaco mais de uma vez, ERRO")

                    return
                }
            }
        }
        
        setWarning() 
    } 

    const CheckTXT = (value) =>
    {
        let CurrentLine = value[checkLine(value)].children[0].text

        setLine(CurrentLine)    
       
        //let lastKey = CurrentLine[CurrentLine.length - 1]
        
        //console.log('CurrentLine',CurrentLine)
        //console.log('Token',Token)
        //console.log('lastKey',lastKey)

        analyzSpaces(value)
    }
    
    const saveToken = () =>
    {
        console.log('PrevTokens',PrevTokens)
                
        setPrevTokens((prevstate) =>
        {
            let array = prevstate
            array.push({token:CurrentToken,id:TokenID})
            return array
        })
    }

    const CheckKeyPressed = (event) =>
    {
        console.log("CurrentToken",CurrentToken) 

        let addtotoken = true

        if (event.key === 'Enter')
        {
            addtotoken = false

            if(CurrentToken!=='')
            {
                if(TokenID==='instituicao')
                {
                    //ANALIZAR 
                    // console.log('Analisar token',Token)
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertBreak()
                    editor.insertText('MEMORANDO no. ')
                    setTokenID('numero do memorando')
                    setlineIndex(lineIndex + 1)
                }
                else if(TokenID==='numero do memorando')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    setTokenID('local')
                    setlineIndex(lineIndex + 1)
                }
                else if(TokenID==='local')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertText(', ')
                    setTokenID('dia')
                } 
                else if(TokenID==='dia')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertText(' de ')
                    setTokenID('mes')
                }
                else if(TokenID==='mes')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertText(' de ')
                    setTokenID('ano')
                }
                else if(TokenID==='ano')
                {
                    if(CurrentToken.length===4)
                    {
                        saveToken()
                        addtotoken = false
                        setCurrentToken('')
                        event.preventDefault()
                        editor.insertText('.')
                        editor.insertBreak()
                        editor.insertBreak()
                        editor.insertText('De: Departamento de ')
                        
                        setTokenID('depto proponente')
                    }
                    else event.preventDefault()
                }
                else if(TokenID==='depto proponente')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertBreak()
                    editor.insertText('Para: Departamento de ')
                    
                    setTokenID('depto dest')
                }
                else if(TokenID==='depto dest')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    if(CurrentToken[CurrentToken.length - 1] === ' ')
                    {
                        editor.insertText('/ ')
                    }
                    else 
                    {
                        editor.insertText(' / ')
                    }
                    setTokenID('pronome tratamento')
                } 
                else if(TokenID==='pronome tratamento')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertText('. ')
                    setTokenID('cargo dest')
                } 
                else if(TokenID==='cargo dest') 
                { 
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertText(' ')
                    setTokenID('nome dest')
                }
                else if(TokenID==='nome dest')
                {    
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertBreak()
                    editor.insertText('Assunto: ')
                    setTokenID('assunto')
                }
                else if(TokenID==='assunto')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertBreak()
                    editor.insertBreak()
                    for(let i = 0; i < PrevTokens.length; i++)
                    {
                        if(PrevTokens[i].id === 'pronome tratamento')
                        {
                            editor.insertText(PrevTokens[i].token+'. ')
                        }
                        else if(PrevTokens[i].id === 'cargo dest')
                        {
                            editor.insertText(PrevTokens[i].token)
                        }
                    }
                    editor.insertBreak()
                    setTokenID('descricao')
                }
                else if(TokenID==='descricao')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertBreak()
                    editor.insertBreak()
                    editor.insertText(`Atenciosamente,`)
                    editor.insertBreak()
                    editor.insertBreak()
                    setTokenID('nome proponente')
                }
                else if(TokenID==='nome proponente')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertBreak()
                    setTokenID('cargo proponente')
                }
                else if(TokenID==='cargo proponente')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    if(CurrentToken[CurrentToken.length - 1] === ' ')
                    {
                        editor.insertText(`do Departamento `)
                    }
                    else 
                    {
                        editor.insertText(` do Departamento `)
                    }

                    for(let i = 0; i < PrevTokens.length; i++)
                    {
                        if(PrevTokens[i].id === 'depto proponente')
                        {
                            editor.insertText(PrevTokens[i].token)
                        }
                    }
                }
            }
            else event.preventDefault()
        }
        else if (event.key === ' ')
        {
            if(CurrentToken!=='')
            {
                if(TokenID==='numero do memorando')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertBreak()
                    setTokenID('local')
                }
                else if(TokenID==='local')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertText(', ')
                    setTokenID('dia')
                } 
                else if(TokenID==='dia')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertText(' de ')
                    setTokenID('mes')
                }
                else if(TokenID==='mes')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertText(' de ')
                    setTokenID('ano')
                }
                else if(TokenID==='ano')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertText('.')
                    editor.insertBreak()
                    editor.insertBreak()
                    editor.insertText('De: Departamento de ')
                    
                    setTokenID('depto proponente')
                }
                else if(TokenID==='pronome tratamento')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertText('. ')
                    setTokenID('cargo dest')
                } 
                else if(TokenID==='cargo dest')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertText(' ')
                    setTokenID('nome dest')
                } 
                else if(TokenID==='nome dest')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertBreak()
                    editor.insertText('Assunto: ')
                    setTokenID('assunto')
                } 
                else if(TokenID==='cargo proponente')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertText(` do Departamento `)

                    for(let i = 0; i < PrevTokens.length; i++)
                    {
                        if(PrevTokens[i].id === 'depto proponente')
                        {
                            editor.insertText(PrevTokens[i].token)
                        }
                    }
                }
            }
            else 
            {
                event.preventDefault()  
                addtotoken = false
            }
        }
        else if(event.key === ',')
        {
            if(TokenID==='local')
            {
                saveToken()
                addtotoken = false
                setCurrentToken('')
                event.preventDefault()
                editor.insertText(', ')
                setTokenID('dia')
            } 
        }
        else if(event.key === '.')
        {
            if(TokenID==='pronome tratamento')
            {
                saveToken()
                addtotoken = false
                setCurrentToken('')
                event.preventDefault()
                editor.insertText('. ')
                setTokenID('cargo dest')
            } 
        }
        else if(event.key === '/')
        {
            if(TokenID==='depto dest')
            {
                if(CurrentToken[CurrentToken.length - 1] === ' ')
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertText('/ ')
                    setTokenID('pronome tratamento')
                }
                else 
                {
                    saveToken()
                    addtotoken = false
                    setCurrentToken('')
                    event.preventDefault()
                    editor.insertText(' / ')
                    setTokenID('pronome tratamento')
                }
                
            } 
        }
        else
        {
            if(TokenID==='numero do memorando')
            {
                if(!isNumber(event.key)) 
                {
                    event.preventDefault()
                    addtotoken = false
                }
               
            }
            if(TokenID==='dia')
            {
                if(CurrentToken.length >= 2)
                {
                    event.preventDefault()
                    addtotoken = false
                }
                if(!isNumber(event.key)) 
                {
                    event.preventDefault()
                    addtotoken = false
                }
               
            }
            if(TokenID==='mes')
            {
                if(isNumber(event.key)) 
                {
                    event.preventDefault()
                    addtotoken = false
                }
               
            }
            if(TokenID==='ano')
            {
                if(CurrentToken.length >= 4)
                {
                    if(event.key !== 'Backspace')
                    {
                        event.preventDefault()
                        addtotoken = false
                    }
                   
                }
                if(!isNumber(event.key)) 
                {
                    event.preventDefault()
                    addtotoken = false
                }
               
            }
        }

        if(addtotoken)
        {
            setCurrentToken((prevstate)=>
            {
                if(event.key === 'Backspace')
                {
                    if(prevstate.length > 0) return prevstate.slice(0,prevstate.length - 1)
                    else return prevstate
                }
                if(CanAdd(event.key))
                {
                    if(prevstate.length > 0) return prevstate + event.key
                    else return event.key
                }
                else return prevstate
               
            })
        }

        adjustLinebyArrows(event.key)
    }

    const CanAdd = (key) =>
    {
        if(key==='CapsLock')return false
        else if(key==='ArrowUp')return false
        else if(key==='ArrowDown')return false
        else if(key==='ArrowLeft')return false
        else if(key==='ArrowRight')return false
        else if(key==='Tab')return false
        return true
    }

    const adjustLinebyArrows = (key) =>
    {
        if (key === 'ArrowUp')
        {
            if(lineIndex>0) 
            {
                //console.log("lineIndex", lineIndex-1)
                setlineIndex(lineIndex - 1)      
            }   
            return
        }
        else if(key === 'ArrowDown')
        {         
            if(editor.children[lineIndex + 1]) 
            {
               // console.log("lineIndex", lineIndex + 1)
                setlineIndex(lineIndex + 1)    
            }
                
            return
        }
    }

    const checkLine = (value) =>
    {
        let line = lineIndex
        if(!value[lineIndex])
        {
            setlineIndex(lineIndex - 1)
            return line - 1
        }
        return line
    }

    return (
    <div className='center'>
        <div style={{
            display:'flex',
            flexDirection:'row',
            marginLeft:'5%'
            }}>
            <p style={{color: 'rgb(140, 140, 140)',}}>Voce esta editando: </p>
            <p style={{color:'rgb(0, 200, 0)', marginLeft:'0.4rem',}}>{TokenID}</p>
            <p style={{color:'rgb(200, 0, 0)', marginLeft:'0.4rem',}}>{warning}</p>
        
        </div>
        
        <div className='EditorContainer'>
            <Slate editor={editor} value={initialText} onChange={(value)=>
            { 
                CheckTXT(value)
            }}>
                <Editable 
                className='textContainer'
                placeholder="Digite aqui..." 
                onKeyDown={(event)=>
                {                     
                    CheckKeyPressed(event)
                }}
                
                />
            </Slate>
        </div>    
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


export default Editor