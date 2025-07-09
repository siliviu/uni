using System.Configuration;
using networking.Server;
using project_cs.repo;
using project_cs.service;
using project_cs.utils;

class StartServer {
    private static readonly int DefaultPort = 55556;
    private static readonly String DefaultIp = "127.0.0.1";

    static void Main(string[] args) {
        Console.WriteLine("Reading properties from app.config ...");
        var port = DefaultPort;
        var ip = DefaultIp;
        var portS = ConfigurationManager.AppSettings["port"];
        if (portS == null) {
            Console.WriteLine("Port property not set. Using default value " + DefaultPort);
        }
        else {
            var result = Int32.TryParse(portS, out port);
            if (!result) {
                Console.WriteLine("Port property not a number. Using default value " + DefaultPort);
                port = DefaultPort;
                Console.WriteLine("Portul " + port);
            }
        }

        var ipS = ConfigurationManager.AppSettings["ip"];

        if (ipS == null) {
            ipS = ip;
            Console.WriteLine("Port property not set. Using default value " + DefaultIp);
        }

        Console.WriteLine("Configuration Settings for database {0}", GetConnectionStringByName("projectDB"));
        IDictionary<String, string> props = new SortedList<String, String>();
        props.Add("ConnectionString", GetConnectionStringByName("projectDB"));
        IUserRepository userRepository = new UserDbRepository(props);
        IChildRepository childRepository = new ChildDbRepository(props);
        ISignupRepository signupRepository = new SignupDbRepository(props);
        var loginService = new LoginService(userRepository);
        var userService = new UserService(childRepository, signupRepository);
        IMasterService service = new MasterService(loginService, userService);
        Console.WriteLine("Starting server on IP {0} and port {1}", ipS, port);
        AbstractConcurrentServer server = new JsonConcurrentServer(ipS, port, service);
        server.Start();
        Console.WriteLine("Server started ...");
        //Console.WriteLine("Press <enter> to exit...");
        Console.ReadLine();
    }


    static string GetConnectionStringByName(string name) {
        // Assume failure.
        string returnValue = null;

        // Look for the name in the connectionStrings section.
        var settings = ConfigurationManager.ConnectionStrings[name];

        // If found, return the connection string.
        if (settings != null)
            returnValue = settings.ConnectionString;

        return returnValue;
    }
}

// public class SerialChatServer : ConcurrentServer {
//     private IChatServices server;
//     private ChatClientWorker worker;
//
//     public SerialChatServer(string host, int port, IChatServices server) : base(host, port) {
//         this.server = server;
//         Console.WriteLine("SerialChatServer...");
//     }
//
//     protected override Thread createWorker(TcpClient client) {
//         worker = new ChatClientWorker(server, client);
//         return new Thread(new ThreadStart(worker.run));
//     }
// }