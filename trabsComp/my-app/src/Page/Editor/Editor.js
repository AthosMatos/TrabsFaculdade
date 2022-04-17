import { useState } from 'react';
import './Editor.css';

const Header = () =>
{
    const [s,sets] = useState()

    const height = useState(20)

    return (
        <div className='EditorContainer'>
            
            <textarea
            className='InputStyle'
            value={s}
            onChange={()=>{}}
            rows={44}
            cols={1}
            onScroll={()=>{console.log('scrolled')}}
            />
        </div>
    )
};

export default Header;