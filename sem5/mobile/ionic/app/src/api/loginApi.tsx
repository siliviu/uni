import { axiosInstance } from "../core";

export interface AuthProps {
    token: string;
}
export const loginApi = (username?: string, password?: string) => {
    return axiosInstance.post<AuthProps>(`login`, { username, password })
}