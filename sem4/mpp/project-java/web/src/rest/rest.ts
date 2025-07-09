import { Signup } from "../domain.ts";

const URL = 'http://localhost:8080/competition/signups'

function status(response: Response) {
    console.log('response status ' + response.status);
    if (response.status >= 200 && response.status < 300) {
        return Promise.resolve(response)
    } else {
        return Promise.reject(new Error(response.statusText))
    }
}

function json(response: Response) {
    return response.json()
}

export function GetSignups() {
    let headers = new Headers();
    headers.append('Accept', 'application/json');
    let myInit: RequestInit = {
        method: 'GET',
        headers: headers,
        mode: 'cors'
    };
    let request = new Request(URL, myInit);
    return fetch(request)
        .then(status)
        .then(json)
        .catch(error => Promise.reject(error));
}

export function DeleteSignup(signup: Signup) {
    let headers = new Headers();
    let myInit: RequestInit = {
        method: 'DELETE',
        headers: headers,
        mode: 'cors'
    };
    let request = new Request(URL + `/${signup.id}`, myInit);
    return fetch(request)
        .then(status)
}

export function ModifySignup(id: String, signup: Signup) {
    let headers = new Headers();
    headers.append('Content-Type', 'application/json');
    let myInit: RequestInit = {
        method: 'PUT',
        headers: headers,
        body: JSON.stringify(signup),
        mode: 'cors'
    };
    let request = new Request(URL + `/${id}`, myInit);
    return fetch(request)
        .then(status)
        .then(json)
        .catch(error => Promise.reject(error));
}

export function AddSignup(signup: Signup) {
    let headers = new Headers();
    headers.append('Content-Type', 'application/json');
    let myInit: RequestInit = {
        method: 'POST',
        headers: headers,
        body: JSON.stringify(signup),
        mode: 'cors'
    };
    let request = new Request(URL, myInit);
    return fetch(request)
        .then(status)
        .then(json)
        .catch(error => Promise.reject(error));
}