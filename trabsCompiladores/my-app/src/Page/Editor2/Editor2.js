import React, { useEffect, useMemo, useState } from 'react'
import { createEditor, Descendant } from 'slate'
import { Slate, Editable, withReact } from 'slate-react'
import { withHistory, } from 'slate-history'
import './Editor2.css';

const Editor2 = () => 
{
    const [CurrentToken,setCurrentToken] = useState({})
    const [Tokens,setTokens] = useState([])
    const [TokenID,setTokenID] = useState('instituicao')
    const [warning,setWarning] = useState()
    const [WholeTXT,setWholeTXT] = useState('')
    const [indexStart,setindexStart] = useState(0)
    const [indexEnd,setindexEnd] = useState(0)

    const editor = useMemo(() => withHistory(withReact(createEditor())),[])

    useEffect(()=>
    {
        if(WholeTXT)
        {
            setCurrentToken({
                id:TokenID,
                token:WholeTXT.slice(indexStart,indexEnd),
                indexStart:indexStart,
                indexEnd:indexEnd
            })
            //saveToken()
        }

    },[WholeTXT])
 
    useEffect(()=>
    {
        if(CurrentToken)
        {
            console.log(CurrentToken)
            setindexEnd(indexEnd + 1)
        }

    },[CurrentToken])

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
                    //console.log("Espaco mais de uma vez, ERRO")

                    return
                }
            }
        }
        
        setWarning() 
    } 

    const CheckTXT = (value) =>
    {
        setWholeTXT(()=>
        {
            let txt = ''
            for(let i = 0; i < value.length ; i++)
            {
                txt += value[i].children[0].text
                if((i + 1) != value.length) txt += '\n'
            }
            return txt
        })        
       
       
        analyzSpaces(value)
    }
    
    const saveToken = () =>
    {              
        console.log(Tokens)
          
        setTokens((prevstate) =>
        {
            let array = prevstate
            array.push(CurrentToken)
            return array
        })
        setindexStart(indexEnd)
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
                    if(event.key==='Enter')
                    {
                        console.log('savetoken')
                        saveToken()
                    }
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


export default Editor2