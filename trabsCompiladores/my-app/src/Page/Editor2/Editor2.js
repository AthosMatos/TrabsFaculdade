import React, { useEffect, useState } from 'react'
import './Editor2.css';
import { TokensData } from './PreData/TokensPreData';
import TextBox from './components/textBox'
import { CompileButton } from './components/CompileButton';
import { ForDummiesSwitch } from './components/ForDummiesSwitch';
import { analyZSpaces, analyZToken } from './Analysis/AnalysisFuncs';
import { useToasts } from 'react-toast-notifications';

const Editor2 = () => 
{
    const [CompiledErros,setCompiledErros] = useState([])
    const [CompiledWarnings,setCompiledWarnings] = useState([])
    const [updateHelper,setupdateHelper] = useState(false)
    const [WholeTXT,setWholeTXT] = useState('')
    const [criticalError,setcriticalError] = useState()
    const { addToast,removeAllToasts } = useToasts();

    //consertando numeros com 0 na frente

    useEffect(()=>
    {      
        if(CompiledErros.length || CompiledWarnings.length)
        {
            console.log('CompiledErros',CompiledErros)
            console.log('CompiledWarnings',CompiledWarnings)
            console.log('criticalError',criticalError)

            CompiledErros.forEach((value,indez,array)=>
            {
                addToast(value.erro, { appearance: 'error' ,autoDismiss:true});
            })
            CompiledWarnings.forEach((value,indez,array)=>
            {
                addToast(value.warning, { appearance: 'warning' ,autoDismiss:true});
            })
            setCompiledErros([])
            setCompiledWarnings([])
            //setcriticalError()
        }
       
    },[updateHelper])


    function Compile (value)
    {
        //console.log(WholeTXT)
        //removeAllToasts()
        
        analyZSpaces({WholeTXT,setCompiledErros})

        analyZToken({setCompiledErros,setCompiledWarnings,setcriticalError,WholeTXT})  
        
        setupdateHelper(!updateHelper)
        
    }


    return (
    <div className='center'>

      

        <ForDummiesSwitch/>
          
        <TextBox setWholeTXT = {setWholeTXT} WholeTXT = {WholeTXT} criticalError={criticalError}/>

        <CompileButton Compile={Compile}/>
       
    </div>
    )
}

const initialText = 
[
  { 
    type: 'paragraph',
    children: 
    [
        { text: 'dsasdaasddsaadadasd' },
        
    ],
  },
]


export default Editor2