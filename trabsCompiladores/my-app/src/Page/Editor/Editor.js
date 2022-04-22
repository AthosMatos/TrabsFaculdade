import React, { useEffect, useMemo, useState } from 'react'
import { createEditor, Descendant } from 'slate'
import { Slate, Editable, withReact } from 'slate-react'
import { withHistory, } from 'slate-history'
import './Editor.css';

const Editor = () => 
{
    const [line,setLine] = useState()
    const [CurrentToken,setCurrentToken] = useState()
    const [TokenID,setTokenID] = useState('instituicao')
    const [blockText,setBlockText] = useState(false)
    const [warning,setWarning] = useState()
    const [lineIndex,setlineIndex] = useState(0)
    const [Helpers,setHelpers] = useState(false)
    const editor = useMemo(() => withHistory(withReact(createEditor())),[])

    useEffect(()=>
    {
        if(CurrentToken)console.log("CurrentToken",CurrentToken)
    })

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
                    setBlockText(true)
                    setWarning("Mais de um espaco entre as palavras")
                    console.log("Espaco mais de uma vez, ERRO")

                    return
                }
            }
        }
        
        setBlockText(false)
        setWarning() 
    } 

    const CheckLine = (value) =>
    {
        let CurrentLine = value[checkLine(value)].children[0].text

        setBlockText(false)

        setLine(CurrentLine)    
       
        //let lastKey = CurrentLine[CurrentLine.length - 1]
        
        //console.log('CurrentLine',CurrentLine)
        //console.log('Token',Token)
        //console.log('lastKey',lastKey)

        analyzSpaces(value)
    }

    const CheckKeyPressed = (event) =>
    {
        //console.log('key',key)
        let addtotoken = true

        if (event.key === 'Enter')
        {
            addtotoken = false

            if(line!=='')
            {
                if(TokenID==='instituicao')
                {
                    //ANALIZAR 
                    // console.log('Analisar token',Token)
                    setCurrentToken()
                    event.preventDefault()
                    editor.insertBreak()
                    editor.insertText('MEMORANDO no. ')
                    setTokenID('numero do memorando')
                    setlineIndex(lineIndex + 1)
                }
                else if(TokenID==='numero do memorando')
                {
                    setCurrentToken()
                    setTokenID('local')
                    setlineIndex(lineIndex + 1)
                }
                else if(TokenID==='local')  event.preventDefault()   
                else if(TokenID==='dia') event.preventDefault()
                else if(TokenID==='mes') event.preventDefault()
                else if(TokenID==='ano') event.preventDefault()
                
            }
        }
        else if(event.key === ',')
        {
            if(TokenID==='local')
            {
                addtotoken = false
                setCurrentToken()
                event.preventDefault()
                editor.insertText(', ')
                setTokenID('dia')
            } 
        }
        else if (event.key === ' ')
        {
            if(TokenID==='dia')
            {
                addtotoken = false
                setCurrentToken()
                event.preventDefault()
                editor.insertText(' de ')
                setTokenID('mes')
            }
        }
        else if(event.key === 'Backspace')
        {
            if(TokenID==='mes')
            {
                setCurrentToken()
                event.preventDefault()
                editor.insertText(' de ')
                setTokenID('ano')
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
                    if(prevstate) return prevstate.slice(0,prevstate.length - 1)
                    else return prevstate
                }
                if(prevstate) return prevstate + event.key
                else return event.key
               
            })
        }

        adjustLinebyArrows(event.key)
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
            <p style={{color:'white', color: 'rgb(140, 140, 140)',}}>Voce esta editando: </p>
            <p style={{color:'rgb(0, 200, 0)', marginLeft:'0.4rem',}}>{TokenID}</p>
            <p style={{color:'rgb(200, 0, 0)', marginLeft:'0.4rem',}}>{warning}</p>
        
        </div>
        
        <div className='EditorContainer'>
            <Slate editor={editor} value={initialText}  onChange={(value)=>
            { 
                CheckLine(value)
            }}>
                <Editable 
                className='textContainer'
                placeholder="Digite aqui..." 
                onKeyDown={(event)=>
                { 
                    if(Helpers)
                    {
                        if(blockText) 
                        {
                            event.preventDefault()//only with helper on
                            setBlockText(false)
                        }
                    }
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