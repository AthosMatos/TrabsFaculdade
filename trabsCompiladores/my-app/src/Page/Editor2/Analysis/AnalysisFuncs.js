import { months, TokensData } from "../PreData/PreMadeData"

let tokens = []//array de tokens
let erros = [] //array de erros
let warnings = [] //array de avisos
let LineErros = []//array de avisos de linha
let OntextToken = '' //string do suposto token que foi escrito
let TokenExpected = undefined //token que o compilador esta esperando
let nextTokenExpected = undefined //prox token depois doq estamos esperando

let TokenIndex = 0 //index de qual token esta sendo analizado
let line = 1 //linha inicial
let lineprevState = 1 //linha inicial
let column = 1 //coluna inicial
let columnprevState = 1 //coluna inicial
let tokensOK = 0 //numero de tokens que estao sem erros para verificacao no final 

function isNumber (value) 
{
    if(parseInt(value) || parseInt(value)===0)
    {
        return true
    }

    return false
}

function isMonth (value)
{
    let ret = false
    months.forEach((month,index,array) =>
    {
        //console.log('value',value)
        //console.log('month',month)
        if(month === value)
        {
            ret = true
        } 
    })
    return ret
}

function Verifyerros(token,setcriticalError)
{
    if(token.hasSomething)
    {
        //console.log('token',token)

        if((token.maxamountcharacters > 0) && (token.TokenValue.length > token.maxamountcharacters))
        {                    
            //console.log('token.TokenValue.length',token.TokenValue.length )
            warnings.push(
            {
                Startlinha:lineprevState,//linha do erro
                Startcoluna:columnprevState,//coluna do warning
                Endlinha:0,//linha do erro
                Endcoluna:columnprevState + OntextToken.length,//coluna do warning
                warning:`Token ${token?.TokenName} contem mais caracteres doque o recomendado`,//erro em si 
                FulllineError:false
            })
        }
                              
        if(token.typeofdata !== 'string&number')
        {
            if(token.typeofdata === 'string' || token.typeofdata === 'number')
            {
                for(let i = 0 ;i < OntextToken.length; i++)
                {
                    if(token.typeofdata === 'string')
                    {
                        if(isNumber(OntextToken[i]))
                        {
                            let erro = {
                                Startlinha:lineprevState,//linha do erro
                                Startcoluna:columnprevState,//coluna do warning
                                Endlinha:0,//linha do erro
                                Endcoluna:columnprevState + OntextToken.length,
                                erro:`Token ${token?.TokenName} nao contem so letras`,//erro em si 
                            }
                            erros.push(erro)                          
                            break
                        }
                    }
                    else if (token.typeofdata === 'number')
                    {
                        if(!isNumber(OntextToken[i]))
                        {
                            let erro = {
                                Startlinha:lineprevState,//linha do erro
                                Startcoluna:columnprevState,//coluna do warning
                                Endlinha:0,//linha do erro
                                Endcoluna:columnprevState + OntextToken.length,
                                erro:`Token ${token?.TokenName} nao contem so numeros`,//erro em si 
                            }
                            erros.push(erro)
                            break
                        }
                    }
                }
            }
    
            else if(token.typeofdata === 'month')
            {
                if(!isMonth(OntextToken))
                {
                    let warning = {
                        Startlinha:lineprevState,//linha do erro
                        Startcoluna:columnprevState,//coluna do warning
                        Endlinha:0,//linha do erro
                        Endcoluna:columnprevState + OntextToken.length,
                        warning:`Token ${token?.TokenName} nao está no formato recomendado (jan,fev,mar...)`,//erro em si
                        FulllineError:false 
                    }
                    warnings.push(warning)
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
            //caso esteja vazio comentar a linha inteira
            Startlinha:lineprevState,//linha do erro
            Startcoluna:0,//coluna do warning
            Endlinha:10000,//linha do erro
            Endcoluna:columnprevState + OntextToken.length,
            erro:`Token ${token.TokenName} vazio`,//erro em si 
            FulllineError:false
        })
    }
}

function copyTokenData()
{
    const TokensDataCpy = []

    for(let i = 0; i<TokensData.length; i++)
    {
        TokensDataCpy.push(
        {
            hasSomething:TokensData[i].hasSomething,
            isDefined:TokensData[i].isDefined,
            TokenName: TokensData[i].TokenName,
            TokenValue:TokensData[i].TokenName,
            cutSequence:TokensData[i].cutSequence,
            typeofdata:TokensData[i].typeofdata,
            maxamountcharacters:TokensData[i].maxamountcharacters,
        })
    }
    return TokensDataCpy
}

function saveToken(value)
{
    //console.log(value.TokenValue)
    //console.log(value.cutSequence)
    let fixaRepetida = false

    tokens.forEach((value2)=>
    {
        if((value2.ValueOfToken === value.cutSequence && value2.nameOfToken==='PalavraFixa'))
        {
            //console.log(`PalavraFixa ${value2.ValueOfToken} repetida`)
            fixaRepetida = true
        }
        if(value2.nameOfToken === value.TokenName && value2.nameOfToken !=='PalavraFixa')
        {
            if(!(value2.ValueOfToken === value.TokenValue))
            {
                console.log(`token ${value2.nameOfToken} repete mas nao esta igual`)
                console.log(`${value2.ValueOfToken} != ${value.TokenValue}`)

                let warning = {
                    Startlinha:lineprevState,//linha do erro
                    Startcoluna:columnprevState,//coluna do warning
                    Endlinha:0,//linha do erro
                    Endcoluna:columnprevState + OntextToken.length,
                    warning:`Token ${value.TokenName} esta diferente de como ele foi orinalmente declarado, verifique o texto`,//erro em si
                    FulllineError:false 
                }
                warnings.push(warning)
                
            }
            else
            {
                //console.log(`token ${value2.nameOfToken} repete`)
            }
            
           //console.log(`${value2.nameOfToken} repete mas nao esta igual`)
        }
        
    })

    if(!fixaRepetida)
    {
        tokens.push({
            nameOfToken:'PalavraFixa',
            ValueOfToken:value.cutSequence,
        })
    }

    tokens.push({
        nameOfToken:value.TokenName,
        ValueOfToken:value.TokenValue,
    })
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

export function analyZToken({WholeTXT,setcriticalError,setCompiledErros,setCompiledWarnings,setTokens})
{
    tokens = [] //zerando de tokens
    erros = [] //zerando de erros
    warnings = [] //zerando de avisos
    LineErros = [] //zerando de avisos
    OntextToken = '' //zerando string do suposto token que foi escrito
    TokenExpected = undefined //zerando token que o compilador esta esperando
    nextTokenExpected = undefined //zerando prox token depois doq estamos esperando
   
    const TokensDataCpy = copyTokenData() //pegando dados fixos para analisar texto

    TokenIndex = 0 //zerando index de qual token esta sendo analizado
    line = 1 //zerando linha inicial
    lineprevState = 1 //zerando linha inicial
    column = 1 //zerando coluna inicial
    columnprevState = 1 //zerando coluna inicial
    tokensOK = 0 //zerando numero de tokens que estao sem erros para verificacao no final 
    
    if(!WholeTXT.length) 
    {
        let erro = {
            Startlinha:0,//linha incial do erro
            Startcoluna:0,//coluna incial do warning
            Endlinha:0,//linha final do erro
            Endcoluna:0,//coluna final do warning
            erro:`nenhum texto digitado`,//erro em si 
            FulllineError:false
        }
        erros.push(erro)
        setCompiledErros(erros)
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

        //console.log('cutSequence' + index,TokensDataCpy[TokenIndex].cutSequence)
        //console.log(TokensDataCpy)
        if(!TokensDataCpy[TokenIndex])console.log('log')

        if(WholeTXT[index] === TokensDataCpy[TokenIndex].cutSequence[cutindex]) 
        {
            if(cutindex === TokensDataCpy[TokenIndex].cutSequence.length - 1)
            {
                //console.log(`Token ${TokensDataCpy[TokenIndex].TokenName} CUTPOINT found`)
                //console.log('token escrito',OntextToken)
                TokensDataCpy[TokenIndex].isDefined = true
                TokensDataCpy[TokenIndex].TokenValue = OntextToken
                
                saveToken(TokensDataCpy[TokenIndex])
               
                if(index + 1 < WholeTXT.length)
                {
                    nextTokenExpected = undefined
                    TokenExpected = undefined
                }
                
                Verifyerros(TokensDataCpy[TokenIndex],setcriticalError)

                //console.log(`Go Analisys next token`)
                columnprevState = column
                lineprevState = line
                if(TokenIndex + 1 !== TokensDataCpy.length) TokenIndex++
                cutindex = 0 
            }
            else cutindex++                
        }
        else 
        {
            OntextToken += WholeTXT[index]
            //console.log('OntextToken',OntextToken)

            if(!TokensDataCpy[TokenIndex].hasSomething && WholeTXT[index]!== ' ' && WholeTXT[index]!== '\n')
            {
                TokensDataCpy[TokenIndex].hasSomething = true
                //console.log(`TokenName ${TokensDataCpy[TokenIndex].TokenName} hasSomething`)
            }                  
        
            cutindex = 0
        } 
    }    
       
    if(tokensOK!=TokensData.length)
    {
        console.log('Missing tokens')
        Verifyerros(TokenExpected,setcriticalError)

        let report

        if(nextTokenExpected)report = `Analise parou no token "${TokenExpected.TokenName}"\nVerifique se o token "${nextTokenExpected.TokenName}" foi definido ou se o texto esta correto`//erro em si 
        else report = `Analise parou no token "${TokenExpected.TokenName}"\nVerifique se o ele esta finalizado ou se o texto esta correto`//erro em si 
            
        //if(nextTokenExpected.hasSomething) report = `Insira "${nextTokenExpected.cutSequence}" para salvar o token "${nextTokenExpected.TokenName}"`//erro em si 
        
        let erro = {
            Startlinha:lineprevState ,//linha incial do erro
            Startcoluna:0,//coluna incial do warning
            Endlinha:0,//linha final do erro
            Endcoluna:1000,//coluna final do erro
            erro:report,
            FulllineError:true
        }
        erros.push(erro)
        LineErros.push(erro)
        //alert here
    }

    setCompiledErros(erros)
    setcriticalError(LineErros)
    setCompiledWarnings(warnings)
    setTokens(tokens)
}
