using System.Net.Sockets;

namespace networking.Proxy;

public abstract class AbstractProxy {
    protected readonly string host;
    protected readonly int port;

    protected NetworkStream stream;
    protected StreamReader streamReader;
    protected StreamWriter streamWriter;

    protected TcpClient connection;

    protected readonly Queue<Response> responses;
    protected volatile bool finished;
    protected EventWaitHandle waitHandle;

    public AbstractProxy(string host, int port) {
        this.host = host;
        this.port = port;
        responses = new Queue<Response>();
    }

    protected void CloseConnection() {
        finished = true;
        try {
            streamReader.Close();
            streamWriter.Close();
            stream.Close();
            connection.Close();
            waitHandle.Close();
        }
        catch (Exception e) {
            Console.WriteLine(e.StackTrace);
        }
    }

    protected Response GetResponse() {
        Response response = null;
        try {
            waitHandle.WaitOne();
            lock (responses) {
                //Monitor.Wait(responses); 
                response = responses.Dequeue();
            }
        }
        catch (Exception e) {
            Console.WriteLine(e.StackTrace);
        }

        return response;
    }

    protected void InitializeConnection() {
        try {
            connection = new TcpClient(host, port);
            stream = connection.GetStream();
            streamReader = new StreamReader(stream);
            streamWriter = new StreamWriter(stream);
            finished = false;
            waitHandle = new AutoResetEvent(false);
            StartReader();
        }
        catch (Exception e) {
            Console.WriteLine(e.StackTrace);
        }
    }

    private void StartReader() {
        var tw = new Thread(Run);
        tw.Start();
    }

    protected abstract bool IsUpdate(Response response);

    protected abstract void HandleUpdate(Response response);

    protected abstract Response ReadResponse();

    public void Run() {
        while (!finished) {
            try {
                var response = ReadResponse();
                Console.WriteLine("response received " + response);
                if (IsUpdate(response)) {
                    HandleUpdate(response);
                }
                else {
                    lock (responses) {
                        responses.Enqueue(response);
                    }

                    waitHandle.Set();
                }
            }
            catch (Exception e) {
                Console.WriteLine("Reading error " + e);
            }
        }
    }
}