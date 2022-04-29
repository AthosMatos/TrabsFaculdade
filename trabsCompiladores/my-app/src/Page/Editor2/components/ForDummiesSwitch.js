import React, { useState } from 'react'
import Switch from "react-switch";

export const ForDummiesSwitch = () =>
{
    const [checked,setChecked] = useState(false)

    return (
        <div style={{
            display:'flex',
            flexDirection:'row',
            alignItems:'center',
            justifyContent:'flex-end'
            }}>
                <p style={{color:'#d3d3d3' ,marginRight:'1rem'}}>Ultra easy mode</p>

                <Switch
                onChange={()=>
                {
                    console.log("Switched")
                    setChecked(!checked)
                }}
                checked={checked}
                id="normal-switch"
                />
              
        </div>
    )
}