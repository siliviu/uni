using System.Configuration;
using networking.Proxy;
using project_cs.utils;

namespace project_cs;

static class Program {
    private const int DefaultPort = 55556;
    private const String DefaultIp = "127.0.0.1";

    /// <summary>
    ///  The main entry point for the application.
    /// </summary>
    [STAThread]
    static void Main() {
        // To customize application configuration such as set high DPI settings or default font,
        // see https://aka.ms/applicationconfiguration.
        ApplicationConfiguration.Initialize();
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
        IMasterService masterService = new MasterJsonProxy(ipS, port);
        var controller = new Controller(masterService);
        Application.Run(new LoginWindow(controller));
    }
}