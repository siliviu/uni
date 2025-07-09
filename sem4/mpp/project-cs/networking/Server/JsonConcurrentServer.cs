using System.Net.Sockets;
using networking.Worker;
using project_cs.utils;

namespace networking.Server;

public class JsonConcurrentServer : AbstractConcurrentServer {
    private IMasterService server;
    private MasterJsonWorker worker;

    public JsonConcurrentServer(string host, int port, IMasterService server) : base(host, port) {
        this.server = server;
        Console.WriteLine("SerialChatServer...");
    }

    protected override Thread CreateWorker(TcpClient client) {
        worker = new MasterJsonWorker(server, client);
        return new Thread(worker.run);
    }
}