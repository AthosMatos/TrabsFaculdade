import { TokensData } from "../PreData/TokensPreData"

export function isNumber (value) 
{
    if(parseInt(value) || parseInt(value)===0)
    {
        return true
    }

    return false
}

export function copyTokenData()
{
    const TokensDataCpy = []

    for(let i = 0; i<TokensData.length; i++)
    {
        TokensDataCpy.push(
        {
            hasSomething:TokensData[i].hasSomething,
            TokenName: TokensData[i].TokenName,
            cutSequence:TokensData[i].cutSequence,
            typeofdata:TokensData[i].typeofdata,
            maxamountcharacters:TokensData[i].maxamountcharacters,
        })
    }
    return TokensDataCpy
}

export function analyZSpaces ({WholeTXT,setCompiledErros})
{     
    let line = 1 //linha inicial
    let column = 1 //coluna inicial

    for(let index = 0; index < WholeTXT.length; index++,column++)
    {
        if(WholeTXT[index] === '\n') //caso tenha um ENTER 
        {
            line++ //adiciona mais uma linha
            column = 1 //reseta as colunas
        }
        
        //caso tenha 2 espacoes em sequencia com um texto entre eles salvar erro
        if(WholeTXT[index] === ' ' && WholeTXT[index + 1] === ' ' && WholeTXT[WholeTXT.length - 1] !== ' ') 
        {
            setCompiledErros((prevstate)=>
            {
                prevstate.push(
                {
                    linha:line,//linha do erro
                    coluna:column,//coluna do erro
                    erro:`Mais de um espaco entre as palavras`,//erro em si 
                })
                return prevstate
            })

            console.log("Espaco mais de uma vez, ERRO")
        }
    }
} 

export function analyZToken({WholeTXT,setcriticalError,setCompiledErros,setCompiledWarnings})
{
    //console.log('TokensData',TokensData)
    let erros = [] //array de erros
    let warnings = [] //array de avisos
    let OntextToken = '' //string do suposto token que foi escrito
    let TokenExpected = undefined //token que o compilador esta esperando
    let nextTokenExpected = undefined //prox token depois doq estamos esperando
   
    const TokensDataCpy = copyTokenData() //pegando dados fixos para analisar texto

    let TokenIndex = 0 //index de qual token esta sendo analizado
    let line = 1 //linha inicial
    let lineprevState = 1 //linha inicial
    let column = 1 //coluna inicial
    let columnprevState = 1 //coluna inicial
    let tokensOK = 0 //numero de tokens que estao sem erros para verificacao no final 

    if(!WholeTXT.length) 
    {
        let erro = {
            Startlinha:0,//linha do erro
            Startcoluna:0,//coluna do warning
            Endlinha:0,//linha do erro
            Endcoluna:0,//coluna do warning
            erro:`nenhum texto digitado`,//erro em si 
        }
        erros.push(erro)
        setCompiledErros(erros)
        setcriticalError(erro)
        return;
    }

    //iterando todo o texto
    for(let index = 0, cutindex = 0; index < WholeTXT.length; index++,column++)
    {
        //console.log(TokensDataCpy[TokenIndex]?.TokenName)

        if(!nextTokenExpected)
        {
            TokenExpected = TokensDataCpy[TokenIndex]
            nextTokenExpected = TokensDataCpy[TokenIndex + 1]
            //console.log('TokenExpected',TokenExpected)
            //console.log('nextTokenExpected',nextTokenExpected)
        }

        if(WholeTXT[index] === '\n') //caso tenha um ENTER 
        {         
            //console.log('adding line and reseting column runs')
            line++ //adiciona mais uma linha
            column = 1 //reseta as colunas
            //console.log('column',column)
        }

        if(WholeTXT[index] === TokensDataCpy[TokenIndex].cutSequence[cutindex]) 
        {
            if(cutindex === TokensDataCpy[TokenIndex].cutSequence.length - 1)
            {
                //console.log(`Token ${TokensDataCpy[TokenIndex].TokenName} CUTPOINT found`)
               // console.log('token escrito',OntextToken)

                if(index + 1 < WholeTXT.length)
                {
                    nextTokenExpected = undefined
                    TokenExpected = undefined
                }
                
                if(TokensDataCpy[TokenIndex].hasSomething)
                {
                    if((TokensDataCpy[TokenIndex].maxamountcharacters > 0) && (OntextToken.length > TokensDataCpy[TokenIndex].maxamountcharacters))
                    {                    
                        warnings.push(
                        {
                            Startlinha:lineprevState,//linha do erro
                            Startcoluna:columnprevState,//coluna do warning
                            Endlinha:0,//linha do erro
                            Endcoluna:columnprevState + OntextToken.length,//coluna do warning
                            warning:`Token ${TokensDataCpy[TokenIndex]?.TokenName} contem mais caracteres doque o recomendado`,//erro em si 
                        })
                    }
                                          
                    if(TokensDataCpy[TokenIndex].typeofdata !== 'string&number')
                    {
                        for(let i = 0 ;i < OntextToken.length; i++)
                        {
                            if(TokensDataCpy[TokenIndex].typeofdata === 'string')
                            {
                                if(isNumber(OntextToken[i]))
                                {
                                    let erro = {
                                        Startlinha:lineprevState,//linha do erro
                                        Startcoluna:columnprevState,//coluna do warning
                                        Endlinha:0,//linha do erro
                                        Endcoluna:columnprevState + OntextToken.length,
                                        erro:`Token ${TokensDataCpy[TokenIndex]?.TokenName} nao contem so letras`,//erro em si 
                                    }
                                    erros.push(erro)
                                    setcriticalError(erro)
                                    break
                                }
                            }
                            else if (TokensDataCpy[TokenIndex].typeofdata === 'number')
                            {
                                if(!isNumber(OntextToken[i]))
                                {
                                    let erro = {
                                        Startlinha:lineprevState,//linha do erro
                                        Startcoluna:columnprevState,//coluna do warning
                                        Endlinha:0,//linha do erro
                                        Endcoluna:columnprevState + OntextToken.length,
                                        erro:`Token ${TokensDataCpy[TokenIndex]?.TokenName} nao contem so numeros`,//erro em si 
                                    }
                                    erros.push(erro)
                                    setcriticalError(erro)
                                    break
                                }
                            }
                        }
                    }   
                    
                    //console.log(`Token ${TokensDataCpy[TokenIndex].TokenName} found`)
                    OntextToken = ''
                    tokensOK++
                }
                else 
                {         
                    //console.log('erros pushing')

                    erros.push(
                    {
                        Startlinha:lineprevState,//linha do erro
                        Startcoluna:columnprevState,//coluna do warning
                        Endlinha:0,//linha do erro
                        Endcoluna:columnprevState + OntextToken.length,
                        erro:`Token ${TokensDataCpy[TokenIndex]?.TokenName} vazio`,//erro em si 
                    })
                }

                //console.log(`Go Analisys next token`)
                columnprevState = column
                lineprevState = line
                TokenIndex++
                cutindex = 0 
            }
            else cutindex++                
        }
        else 
        {
            if(WholeTXT[index]!== ' ' && WholeTXT[index]!== '\n') 
            {
                OntextToken += WholeTXT[index]
                //console.log(token)

                if(!TokensDataCpy[TokenIndex].hasSomething)
                {
                    TokensDataCpy[TokenIndex].hasSomething = true
                    //console.log(`TokenName ${TokensDataCpy[TokenIndex].TokenName} hasSomething`)
                }                  
            }
            cutindex = 0
        }
    }     
       
    if(tokensOK!=TokensData.length)
    {
        console.log('Missing tokens')
        let erro = {
            Startlinha:line ,//linha do erro
            Startcoluna:0,//coluna do warning
            Endlinha:0,//linha do erro
            Endcoluna:1000,
            erro:`Token ${nextTokenExpected?.TokenName} nao foi bem definido, por favor, verifique o texto`,//erro em si 
        }
        erros.push(erro)
        setcriticalError(erro)
        //alert here
    }

    setCompiledErros(erros)
    setCompiledWarnings(warnings)
}