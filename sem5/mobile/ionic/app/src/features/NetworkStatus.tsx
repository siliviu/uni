import { Network } from "@capacitor/network";
import { useContext, useEffect, useRef, useState } from "react";
import { getItems } from "../api/itemApi";
import { AuthContext } from "./AuthProvider";


export const useNetworkStatus = (onChange: any) => {
    const token = useContext(AuthContext).token;
    const [networkStatus, setNetworkStatus] = useState<string>("OFFLINE");
    const [apiStatus, setApiStatus] = useState<string>("OFFLINE");
    let tried = useRef(true);
    useEffect(() => {
        const checkNetworkStatus = async () => {
            try {
                const status = await Network.getStatus();
                setNetworkStatus(status.connected ? 'ONLINE' : 'OFFLINE');
            } catch (error) {
                console.error('Error fetching initial network status:', error);
            }
        };

        const handleNetworkStatusChange = (status: any) => {
            setNetworkStatus(status.connected ? 'ONLINE' : 'OFFLINE');
        };

        checkNetworkStatus();

        const networkStatusListener = Network.addListener(
            'networkStatusChange',
            handleNetworkStatusChange
        );

        const fetchAPIStatus = async () => {
            try {
                await getItems({ page: 211 }, token);
                setApiStatus('ONLINE');
                if (tried.current) {
                    onChange();
                    tried.current = false;
                }
            } catch (error) {
                tried.current = true;
                setApiStatus('OFFLINE');
            }
        };


        const intervalId = setInterval(fetchAPIStatus, 2000)
        return () => {
            clearInterval(intervalId);
        }
    }, []);


    return { networkStatus, apiStatus, setApiStatus }
}