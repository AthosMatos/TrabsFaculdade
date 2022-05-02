import Editor from '../Editor/Editor'
import Editor2 from '../Editor2/Editor2'
import { ToastProvider } from 'react-toast-notifications';

import './App.css';
import { useEffect, useState } from 'react';

const App = () => 
{
  const [editorBeingUsed,setEditorBeingUsed] = useState(false)

  useEffect(()=>
  { 
    console.log(editorBeingUsed)
    
  },[editorBeingUsed])

  return (
    <ToastProvider autoDismissTimeout={80000} transitionDuration={400} >
      <div className='AppContainer2'>
        {!editorBeingUsed 
        ? 
        <Editor2 
        setEditorBeingUsed={setEditorBeingUsed} 
        editorBeingUsed={editorBeingUsed}/> 
        : 
        <Editor 
        setEditorBeingUsed={setEditorBeingUsed} 
        editorBeingUsed={editorBeingUsed}/>}
      </div>
    </ToastProvider>
      
  );
}

export default App;
