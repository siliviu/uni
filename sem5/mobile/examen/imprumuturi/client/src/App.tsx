import { BrowserRouter, Navigate, Route, Routes, useNavigate } from "react-router-dom";
import { IonApp, IonContent, IonHeader, IonPage, IonRouterOutlet, IonTitle, IonToolbar, setupIonicReact } from "@ionic/react";
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
import { useEffect, useState, useRef } from "react";
import { Item } from "./data/item";
import { connect } from "./notifications/notifications";
import { ToastContainer, toast } from "react-toastify";
import "react-toastify/dist/ReactToastify.css";
import { getCachedItems, cacheItems } from "./data/item";

setupIonicReact();

const Login: React.FC = () => {
  const [username, setUsername] = useState("");
  const navigate = useNavigate();

  const handleNext = () => {
    localStorage.setItem("username", username);
    navigate("/home");
  };

  useEffect(() => {
    const storedUsername = localStorage.getItem("username");
    if (storedUsername) {
      navigate("/home");
    }
  }, [navigate]);

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
          <IonTitle>Login</IonTitle>
        </IonToolbar>
      </IonHeader>
      <IonContent fullscreen>
        <input
          type="text"
          value={username}
          onChange={(e) => setUsername(e.target.value)}
          placeholder="Enter username"
        />
        <button onClick={handleNext}>Next</button>
      </IonContent>
    </IonPage>
  );
};

const App: React.FC = () => {
  //PT NOTIFICARI PRIN SOCKET
  const [sentMessage, setSentMessage] = useState<Item>();
  const initial = useRef(true);

  return (
    <IonApp>
      <BrowserRouter>
        <Routes>
          <Route path="/" element={<Navigate to="/login" />} />
          <Route path="/login" element={<Login />} />
          <Route path="/home" element={<Home sentMessage={sentMessage} />} />
        </Routes>
      </BrowserRouter>
      <ToastContainer containerId={"id"} />
    </IonApp>
  );
};

export default App;
