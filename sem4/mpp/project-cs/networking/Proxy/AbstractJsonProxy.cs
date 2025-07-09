using networking.Proxy;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace networking;

public abstract class AbstractJsonProxy : AbstractProxy {
    protected AbstractJsonProxy(string host, int port) : base(host, port) {
        JsonConvert.DefaultSettings = () => {
            var settings = new JsonSerializerSettings {
                NullValueHandling = NullValueHandling.Ignore
            };
            settings.Converters.Add(new StringEnumConverter());
            return settings;
        };
    }

    protected override Response ReadResponse() {
        try {
            Console.WriteLine("reading response");
            var read = streamReader.ReadLine();
            Console.WriteLine("read " + read);
            return JsonConvert.DeserializeObject<Response>(read);
        }
        catch (Exception e) {
            throw new Exception("Error reading response " + e);
        }
    }


    protected void SendRequest(Request request) {
        try {
            var json = JsonConvert.SerializeObject(request);
            Console.WriteLine("writing: " + json);
            streamWriter.WriteLine(json);
            streamWriter.Flush();
            Console.WriteLine("request sent");
        }
        catch (Exception e) {
            throw new Exception("Error sending object " + e);
        }
    }
}