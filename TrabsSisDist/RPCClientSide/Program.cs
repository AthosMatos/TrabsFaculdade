using System;
using System.Net.Http;
using System.Threading.Tasks;
using Grpc.Net.Client;


namespace RPCClientSide
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            // The port number(5001) must match the port of the gRPC server.
         
            var httpHandler = new HttpClientHandler();

            // Return `true` to allow certificates that are untrusted/invalid
            httpHandler.ServerCertificateCustomValidationCallback = HttpClientHandler.DangerousAcceptAnyServerCertificateValidator;

            var channel = GrpcChannel.ForAddress("https://localhost:5001", new GrpcChannelOptions { HttpHandler = httpHandler });

            var client = new Greeter.GreeterClient(channel);
            
            var replyAsync = await client.SayHelloAsync(new HelloRequest { Name = "GreeterClient" });
            
            var reply = client.GetGeladeiraData(new HelloRequest { Name = "GreeterClient" });

            Console.WriteLine("Greeting: " + reply.Message);

            Console.WriteLine("Press any key to exit...");
            Console.ReadKey();
        }
    }
}
