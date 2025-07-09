using System;
using System.Collections;
using System.Net;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Reflection.Metadata;
using System.Threading;
using System.Threading.Tasks;
using Newtonsoft.Json;
using project_cs.domain;

class Client {
    static HttpClient client = new HttpClient(new LoggingHandler(new HttpClientHandler()));
    private static string URL_Base = "http://localhost:8080/app/configurations";

    static void Main(string[] args) {
        client.BaseAddress = new Uri(URL_Base);
        client.DefaultRequestHeaders.Accept.Clear();
        client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));
        RunAsync().Wait();
    }

    static async Task RunAsync() {
        Configuration conf = new Configuration();
        conf.letters = "abcd";
        conf.word1 = "ab";
        conf.word2 = "ac";
        conf.word3 = "ad";
        conf.word4 = "db";
        var s = await CreateConfigAsync(URL_Base, conf);
        Console.WriteLine("Added signup " + s + "(id: " + s.id + ")");
        /*
        Child c = new Child("dorel", 8);
        c.id = 200;
        Signup s = new Signup(c, AgeGroup.TWELVE_FIFTEEN, RaceDistance.THOUSAND);
        Console.WriteLine("Adding signup " + s.ToString());
        s = await CreateSignupAsync(URL_Base, s);
        Console.WriteLine("Added signup " + s + "(id: " + s.id + ")");
        Console.WriteLine("Printing all signups:");
        var res = await GetSignupsAsync(URL_Base);
        foreach (Signup signup in res)
            Console.WriteLine(signup + "(id: " + signup.id + ")");
        Console.WriteLine("Info for signup");
        s = await GetSignupAsync(URL_Base + "/" + s.id);
        Console.WriteLine("Signup " + s + "(id: " + s.id + ")");
        s.raceDistance = RaceDistance.HUNDRED;
        Console.WriteLine("Modifying signup");
        await ModifySignupAsync(URL_Base + "/" + s.id, s);
        s = await GetSignupAsync(URL_Base + "/" + s.id);
        Console.WriteLine("Signup " + s + "(id: " + s.id + ")");
        await DeleteSignupAsync(URL_Base + "/" + s.id);
        res = await GetSignupsAsync(URL_Base);
        foreach (Signup signup in res)
            Console.WriteLine(signup + "(id: " + signup.id + ")");

    }

    /*

    static async Task DeleteSignupAsync(string path) {
        HttpResponseMessage response = await client.DeleteAsync(path);
        if (response.IsSuccessStatusCode) {
            await response.Content.ReadAsStreamAsync();
        }
    }

    static async Task<Signup[]> GetSignupsAsync(string path) {
        Signup[] result = null;
        HttpResponseMessage response = await client.GetAsync(path);
        if (response.IsSuccessStatusCode) {
            result = await response.Content.ReadAsAsync<Signup[]>();
        }

        return result;
    }


    static async Task<Signup> GetSignupAsync(string path) {
        Signup result = null;
        HttpResponseMessage response = await client.GetAsync(path);
        if (response.IsSuccessStatusCode) {
            result = await response.Content.ReadAsAsync<Signup>();
        }

        return result;
    }

    static async Task ModifySignupAsync(string path, Signup signup) {
        HttpResponseMessage response = await client.PutAsJsonAsync(path, signup);
        if (response.IsSuccessStatusCode) {
            await response.Content.ReadAsStreamAsync();
        }
    }


    static async Task<Signup> CreateSignupAsync(string path, Signup signup) {
        Signup result = null;
        HttpResponseMessage response = await client.PostAsJsonAsync(path, signup);
        if (response.IsSuccessStatusCode) {
            result = await response.Content.ReadAsAsync<Signup>();
        }

        return result;
    }
    */
    }


    static async Task<Configuration> CreateConfigAsync(string path, Configuration configuration) {
        Configuration result = null;
        HttpResponseMessage response = await client.PostAsJsonAsync(path, configuration);
        if (response.IsSuccessStatusCode) {
            result = await response.Content.ReadAsAsync<Configuration>();
        }

        return configuration;
        //   return result;
    }
/*
    static async Task ModifyConfig(string path, String config) {
        HttpResponseMessage response = await client.PutAsJsonAsync(path, config);
        if (response.IsSuccessStatusCode) {
            await response.Content.ReadAsStreamAsync();
        }
    }

    private static async Task<Game> GetGameAsync(string path) {
        Game result = null;
        HttpResponseMessage response = await client.GetAsync(path);
        if (response.IsSuccessStatusCode) {
            result = await response.Content.ReadAsAsync<Game>();
        }

        return result;
    }
    */

    public class LoggingHandler : DelegatingHandler {
        public LoggingHandler(HttpMessageHandler innerHandler)
            : base(innerHandler) { }

        protected override async Task<HttpResponseMessage> SendAsync(HttpRequestMessage request,
            CancellationToken cancellationToken) {
            Console.WriteLine("Request:");
            Console.WriteLine(request.ToString());
            if (request.Content != null) {
                Console.WriteLine(await request.Content.ReadAsStringAsync());
            }

            Console.WriteLine();

            HttpResponseMessage response = await base.SendAsync(request, cancellationToken);

            Console.WriteLine("Response:");
            Console.WriteLine(response.ToString());
            if (response.Content != null) {
                Console.WriteLine(await response.Content.ReadAsStringAsync());
            }

            Console.WriteLine();

            return response;
        }
    }
}