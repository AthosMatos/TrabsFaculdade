import React, { useState, useCallback, useMemo } from 'react'
import { Slate, Editable, withReact } from 'slate-react'
import { Text, Descendant, createEditor } from 'slate'
import { css } from '@emotion/css'
import { withHistory } from 'slate-history'

const TextBox = ({setWholeTXT,WholeTXT,criticalError}) => {
  
  const editor = useMemo(() => withHistory(withReact(createEditor())), [])

  const decorate = useCallback(() => {
      let fromLine = criticalError ? criticalError.Startlinha - 1  : 0
      let fromColumn = criticalError? criticalError.Startcoluna - 1 : 0
      let lines = 0
      let toline = fromLine 
      let toColumn = criticalError? criticalError.Endcoluna - 1 : 0

      if(criticalError)
      {
        for(let i = 0; i<WholeTXT.length; i++)
        {
          if(lines + 1 === criticalError.Startlinha)
          {
            toColumn++
          }
          if(WholeTXT[i]==="\n")
          {
            if(toColumn)break
            lines++
          }
        }

        //console.log('criticalError',criticalError)
      }

      //console.log('fromLine',fromLine)
      //console.log('toline',toline)

      return {
        anchor: { path:[fromLine,0], offset: fromColumn },
        focus: { path:[toline,0], offset: toColumn },
        highlight: true,
      }
    },
    [WholeTXT,criticalError]
  )

  return (
    <div className='EditorContainer'>
      <Slate editor={editor} value={initialValue} onChange={(value)=>
        { 
            //console.log(WholeTXT)

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
        decorate={decorate} 
        renderLeaf={props => <Leaf {...props} />}   
        />
      </Slate>
    </div>
  )
}

const Leaf = ({ attributes, children, leaf }) => {
  return (
    <span
      {...attributes}
      {...(leaf.highlight && { 'data-cy': 'search-highlighted' })}
      className={css`
        font-weight: ${leaf.bold && 'bold'};
        background-color: ${leaf.highlight && '#690000'};
      `}
    >
      {children}
    </span>
  )
}

const initialValue = 
[
  { 
    type: 'paragraph',
    children: 
    [
        { text: '' },
        
    ],
  },
]


export default TextBox