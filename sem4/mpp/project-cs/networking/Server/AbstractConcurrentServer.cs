using System.Net.Sockets;

namespace networking.Server;

public abstract class AbstractConcurrentServer : AbstractServer {
    public AbstractConcurrentServer(string host, int port) : base(host, port) { }

    public override void ProcessRequest(TcpClient client) {
        var t = CreateWorker(client);
        t.Start();
    }

    protected abstract Thread CreateWorker(TcpClient client);
}