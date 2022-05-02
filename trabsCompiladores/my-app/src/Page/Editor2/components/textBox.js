import React, { useState, useCallback, useMemo } from 'react'
import { Slate, Editable, withReact } from 'slate-react'
import { Text, Descendant, createEditor } from 'slate'
import { css } from '@emotion/css'
import { withHistory } from 'slate-history'

const TextBox = ({setWholeTXT,WholeTXT,criticalError,CompiledErros,CompiledWarnings}) => {
  
  const editor = useMemo(() => withHistory(withReact(createEditor())), [])

  const decorate = useCallback(() => {

      let ret = []

      CompiledWarnings.forEach((value,index,array) => 
      {
        let highlight = {}

        let fromLine = value.Startlinha - 1 
        let fromColumn = value.Startcoluna - 1 
        let lines = 0
        let toline = fromLine 
        let toColumn = value.Endcoluna - 1 
  
        for(let i = 0; i<WholeTXT.length; i++)
        {
          if(lines + 1 === value.Startlinha)
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

        highlight = {
          anchor: { path:[fromLine,0], offset: fromColumn },
          focus: { path:[toline,0], offset: toColumn },
          highlight: true,
          type:'warning',
          FulllineError:value.FulllineError
        }
        ret.push(highlight)
      });
      
      CompiledErros.forEach((value,index,array) => 
      {
        let highlight = {}

        let fromLine = value.Startlinha - 1 
        let fromColumn = value.Startcoluna - 1 
        let lines = 0
        let toline = fromLine 
        let toColumn = value.Endcoluna - 1 
  
        for(let i = 0; i<WholeTXT.length; i++)
        {
          if(lines + 1 === value.Startlinha)
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

        highlight = {
          anchor: { path:[fromLine,0], offset: fromColumn },
          focus: { path:[toline,0], offset: toColumn },
          highlight: true,
          type:'erro',
          FulllineError:value.FulllineError
        }
        ret.push(highlight)
      });

      //console.log('toline',toline)

      return ret
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

  let classN
  //console.log(leaf.FulllineError)

  if(leaf.FulllineError===true)
  {
    classN = css`
      font-weight: ${leaf.bold && 'bold'};
      background-color: ${leaf.highlight && '#1e309b'};`
  }
  else
  {
    if(leaf.type === 'erro')
    {
      classN = css`
        font-weight: ${leaf.bold && 'bold'};
        background-color: ${leaf.highlight && '#690000'};`
      
    }
    else
    {
      classN = css`
        font-weight: ${leaf.bold && 'bold'};
        background-color: ${leaf.highlight && '#a78e01'};`
    }
  }

  return (
    <span
      {...attributes}
      {...(leaf.highlight && { 'data-cy': 'search-highlighted' })}
      className={classN}
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