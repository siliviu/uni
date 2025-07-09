export const getLogger: (tag: string) => (...args: any) => void =
  tag => (...args) => console.log(tag, ...args);

import axios from "axios";

export const axiosInstance = axios.create({
  baseURL: "http://localhost:3000",
  headers: {
    "Content-Type": "application/json",
  }
})

export const authConfig = (token?: string) => ({
  headers: {
    Authorization: `Bearer ${token}`
  }
})