import React from 'react'

export const CompileButton = ({Compile}) =>
{
    return (
        <button style={
            {
                boxShadow: '0.0rem 0.0rem 1.5rem',
                marginTop:'1rem',
                width:'7rem',
                height:'3.5rem',
                borderRadius:'20rem',
                backgroundColor:'#d3d3d3',
                color:'#181818'
            }} 
            onClick={()=>
            {
                Compile()
                //console.log("ButtonClick")
                
            }}>
                Compilar
        </button>
    )
}