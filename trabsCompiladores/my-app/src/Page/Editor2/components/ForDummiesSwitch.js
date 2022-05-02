import React, { useState } from 'react'
import Switch from "react-switch";

export const ForDummiesSwitch = ({setEditorBeingUsed,editorBeingUsed}) =>
{
    return (
        <>
            <p style={{color:'#d3d3d3' ,marginRight:'1rem'}}>Typing for dummies</p>

            <Switch
            onChange={()=>
            {
                console.log("Switched")
                setEditorBeingUsed(!editorBeingUsed)
            }}
            checked={editorBeingUsed}
            id="normal-switch"
            />
        </>        
    )
}