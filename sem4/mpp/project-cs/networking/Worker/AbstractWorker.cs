using System.Net.Sockets;

namespace networking.Worker;

public abstract class AbstractWorker {
    protected TcpClient connection;

    protected NetworkStream stream;
    protected StreamReader streamReader;
    protected StreamWriter streamWriter;
    protected volatile bool connected;
    protected static Response okResponse;

    public AbstractWorker(TcpClient connection) {
        this.connection = connection;
        okResponse = new Response() {
            type = ResponseType.OK
        };
        try {
            stream = connection.GetStream();
            streamReader = new StreamReader(stream);
            streamWriter = new StreamWriter(stream);
            connected = true;
        }
        catch (Exception e) {
            Console.WriteLine(e.StackTrace);
        }
    }

    public void run() {
        while (connected) {
            try {
                var request = ReadRequest();
                var response = HandleRequest(request);
                if (response != null) {
                    SendResponse(response);
                }
            }
            catch (Exception e) {
                if (!connection.Connected)
                    connected = false;
                Console.WriteLine(e.StackTrace);
            }

            try {
                Thread.Sleep(50);
            }
            catch (Exception e) {
                Console.WriteLine(e.StackTrace);
            }
        }

        try {
            streamReader.Close();
            streamWriter.Close();
            stream.Close();
            connection.Close();
        }
        catch (Exception e) {
            Console.WriteLine("Error " + e);
        }
    }

    protected abstract Request ReadRequest();
    protected abstract Response HandleRequest(Request request);
    protected abstract void SendResponse(Response response);
}