using Grpc.Core;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace RPCServerSide
{
    public class GreeterService : Greeter.GreeterBase
    {
        struct GeladeiraDados
        {
            public int qntComida;
            public float temperaturaFreezer;
            public float temperatura;

            public GeladeiraDados(int qntComida,float temperaturaFreezer,float temperatura)
            {
               this.temperatura = temperatura;
               this.qntComida = qntComida;
               this.temperaturaFreezer = temperaturaFreezer;
            }

        };
        GeladeiraDados geladeira;


        private readonly ILogger<GreeterService> _logger;
        public GreeterService(ILogger<GreeterService> logger)
        {
            _logger = logger;
           // geladeira2 = "gela";
            geladeira = new GeladeiraDados(0, 0.0f, 0.0f);
        }

        public override Task<HelloReply> SayHello(HelloRequest request, ServerCallContext context)
        {
            return Task.FromResult(new HelloReply
            {
                Message = "Hello " + request.Name
            });
        }
        public override Task<HelloReply> GetGeladeiraData(HelloRequest request, ServerCallContext context)
        {
            return Task.FromResult(new HelloReply
            {
                Message = "Geladeira temp: " + geladeira.temperatura
            });
        }
    }
}
