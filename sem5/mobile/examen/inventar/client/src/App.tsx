import { BrowserRouter, Navigate, Route, Routes } from "react-router-dom";
import { IonApp, IonRouterOutlet, setupIonicReact } from "@ionic/react";
import Home from "./pages/Home";

/* Core CSS required for Ionic components to work properly */
import "@ionic/react/css/core.css";

/* Basic CSS for apps built with Ionic */
import "@ionic/react/css/normalize.css";
import "@ionic/react/css/structure.css";
import "@ionic/react/css/typography.css";

/* Optional CSS utils that can be commented out */
import "@ionic/react/css/padding.css";
import "@ionic/react/css/float-elements.css";
import "@ionic/react/css/text-alignment.css";
import "@ionic/react/css/text-transformation.css";
import "@ionic/react/css/flex-utils.css";
import "@ionic/react/css/display.css";

/* Theme variables */
import "./theme/variables.css";
import { useEffect, useState } from "react";
import { Item } from "./data/item";
import { connect } from "./notifications/notifications";
import { ToastContainer } from "react-toastify";
import "react-toastify/dist/ReactToastify.css";
import { Product } from "./data/product";

setupIonicReact();

const App: React.FC = () => {
  //PT NOTIFICARI PRIN SOCKET
  const [sentMessage, setSentMessage] = useState<Product>();
  useEffect(() => {
    const webSocket = connect(setSentMessage);
    return () => {
      if (webSocket.readyState === WebSocket.OPEN) {
        webSocket.close();
      }
    };
  }, []);

  return (
    <>
      <Home sentMessage={sentMessage} />
    </>
  );
};

export default App;
