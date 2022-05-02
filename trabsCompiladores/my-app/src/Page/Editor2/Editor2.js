import React, { useEffect, useState } from 'react'
import './Editor2.css';
import { TokensData } from './PreData/PreMadeData';
import TextBox from './components/textBox'
import { CompileButton } from './components/CompileButton';
import { ForDummiesSwitch } from './components/ForDummiesSwitch';
import { analyZSpaces, analyZToken } from './Analysis/AnalysisFuncs';
import { useToasts } from 'react-toast-notifications';

const Editor2 = ({setEditorBeingUsed,editorBeingUsed}) => 
{
    const [CompiledErros,setCompiledErros] = useState([])
    const [CompiledWarnings,setCompiledWarnings] = useState([])
    const [updateHelper,setupdateHelper] = useState(false)
    const [WholeTXT,setWholeTXT] = useState('')
    const [LineErros,setLineErros] = useState([])
    const [Tokens,setTokens] = useState([])

    const { addToast,removeAllToasts,removeToast } = useToasts();
    //consertando numeros com 0 na frente

    useEffect(()=>
    {      
        if(CompiledErros.length || CompiledWarnings.length || LineErros.length)
        {
            //console.log('CompiledErros',CompiledErros)
            //console.log('CompiledWarnings',CompiledWarnings)
            //console.log('LineErros',LineErros)
            console.log('Tokens',Tokens)

            // addToast(`${value.erro}. *linha:${value.Startlinha} coluna: ${value.Startcoluna}*`, 
            LineErros.forEach((value,indez,array)=>
            {
               addToast(`${value.erro} *linha:${value.Startlinha}*`, 
               { appearance: 'info' ,autoDismiss:true});
            })

            CompiledWarnings.forEach((value,indez,array)=>
            {
                addToast(`${value.warning} *linha:${value.Startlinha}*`, { appearance: 'warning' ,autoDismiss:true});
            })

            CompiledErros.forEach((value,indez,array)=>
            {
                if(!value.FulllineError)addToast(`${value.erro} *linha:${value.Startlinha}*`, { appearance: 'error' ,autoDismiss:true});
            })
            
            setCompiledErros([])
            setCompiledWarnings([])
        }
       
    },[updateHelper])


    function Compile (value)
    {
        //console.log(WholeTXT)
        removeAllToasts()
        
        analyZSpaces({WholeTXT,setCompiledErros})

        analyZToken({setCompiledErros,setCompiledWarnings,setcriticalError: setLineErros,WholeTXT,setTokens})  
        
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
                <ForDummiesSwitch 
                setEditorBeingUsed={setEditorBeingUsed}
                editorBeingUsed={editorBeingUsed}/>
        </div>
        
        <TextBox 
        setWholeTXT = {setWholeTXT} 
        WholeTXT = {WholeTXT} 
        criticalError={LineErros} 
        CompiledErros={CompiledErros}
        CompiledWarnings={CompiledWarnings}
        />

        <CompileButton Compile={Compile}/>
       
    </div>
    )
}

export default Editor2