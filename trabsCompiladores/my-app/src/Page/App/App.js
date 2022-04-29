import Editor from '../Editor/Editor'
import Editor2 from '../Editor2/Editor2'
import { ToastProvider } from 'react-toast-notifications';

import './App.css';

const App = () => 
{
  return (
    <ToastProvider autoDismissTimeout={80000} transitionDuration={400} >
      <div className='AppContainer2'>
        <Editor2/>
      </div>
    </ToastProvider>
      
  );
}

export default App;
