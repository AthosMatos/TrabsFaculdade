import React, { useEffect, useMemo, useState } from 'react'
import { createEditor, Descendant, Text as SlateText } from 'slate'
import { Slate, Editable, withReact } from 'slate-react'
import { withHistory, } from 'slate-history'
import './Editor.css';

const Editor = () => 
{
    const [WhatsNow,setWhatsNow] = useState('')
    const editor = useMemo(() => withHistory(withReact(createEditor())), [])
    const [frase,setFrase] = useState('')
    const [token,setToken] = useState('')

    useEffect(()=>
    {
        console.log("frase",frase)

    },[frase])

    return (
    <div className='center'>
        <div className='EditorContainer'>
            <Slate editor={editor} value={initialText} >
                <Editable 
                className='textContainer'
                placeholder="Digite aqui..." 
                onKeyDown={event => 
                {
                    // console.log("event.key.length",event)

                    if (event.key == 'Enter' || event.key == ' ')
                    {
                        if(frase!='')
                        {
                            //ANALIZAR FRASE 
                            console.log('Analisar frase',frase)
                            setFrase('')
                        }
                       
                    }
                    else
                    {
                        if(event.key.length == 1)
                        {                       
                            setFrase((prevState)=>
                            {
                                return prevState + event.key
                            })
                        }   
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


export default Editor