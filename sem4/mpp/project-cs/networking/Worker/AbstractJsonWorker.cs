using Newtonsoft.Json;
using System.Net.Sockets;
using Newtonsoft.Json.Converters;

namespace networking.Worker;

public abstract class AbstractJsonWorker : AbstractWorker {
    protected AbstractJsonWorker(TcpClient connection) : base(connection) {
        JsonConvert.DefaultSettings = () => {
            var settings = new JsonSerializerSettings {
                NullValueHandling = NullValueHandling.Ignore
            };
            settings.Converters.Add(new StringEnumConverter());
            return settings;
        }; 
    }

    protected override Request ReadRequest() {
        try {
            Console.WriteLine("reading request");
            var read = streamReader.ReadLine();
            Console.WriteLine("read " + read);
            return JsonConvert.DeserializeObject<Request>(read);
        }
        catch (Exception e) {
            throw new Exception("Error reading request " + e);
        }
    }

    protected override void SendResponse(Response response) {
        Console.WriteLine("sending response " + response);
        lock (stream) {
            var json = JsonConvert.SerializeObject(response);
            Console.WriteLine("writing: " + json);
            streamWriter.WriteLine(json);
            streamWriter.Flush();
            Console.WriteLine("response sent");
        }
    }
}