import {
  IonContent,
  IonHeader,
  IonPage,
  IonTitle,
  IonToolbar,
} from "@ionic/react";
import "./Home.css";
import { Item, getCachedItems, cacheItems } from "../data/item";
import { useEffect, useRef, useState } from "react";
import { useConnection } from "../notifications/connection";
import { toast } from "react-toastify";
import { ToastContainer } from "react-toastify";
import "react-toastify/dist/ReactToastify.css";
import { connect } from "../notifications/notifications";
import axios from "axios";

export interface Home {
  sentMessage: Item | undefined;
}
const Home: React.FC<Home> = ({ sentMessage }) => {
  //PT HANDLE ONLINE/OFFLINE
  const firstRender = useRef(true);
  const initial = useRef(true);
  const [isOnline, setIsOnline] = useConnection();
  const [labelOnline, setLabelOnline] = useState(false);
  useEffect(() => {
    if (!isOnline) {
      setLabelOnline(false);
    } else {
      setLabelOnline(true);
    }
  }, [isOnline]);

  //PT NOTIFICARI PRIN SOCKET
  useEffect(() => {
    toast(sentMessage?.name);
  }, [sentMessage]);

  const [items, setItems] = useState<Item[]>(getCachedItems());
  const username = localStorage.getItem("username") || "";

  useEffect(() => {
    if (firstRender.current && initial.current) {
      firstRender.current = false;
      setItems(getCachedItems());
    }
    const webSocket = connect((newItems: Item[]) => {
      if (initial.current) {
        initial.current = false;
        setItems(newItems);
        cacheItems(newItems);
        toast("Items downloaded");
      } else {
        toast("Update received");
        setItems((prevItems) => {
          if (!Array.isArray(prevItems)) return prevItems;
          const newItem = Array.isArray(newItems) ? newItems[0] : newItems;
          const itemIndex = prevItems.findIndex((item) => item.id === newItem.id);
          let updatedItems;
          if (itemIndex !== -1) {
            updatedItems = prevItems.map((item) => (item.id === newItem.id ? newItem : item));
          } else {
            updatedItems = [...prevItems, newItem];
          }
          cacheItems(updatedItems);
          return updatedItems;
        });
      }
    });
    return () => {
      webSocket.close();
    };
  }, []);

  const getItemBackgroundColor = (item: Item) => {
    if (item.takenBy === username) return "red";
    if (item.desiredBy && item.desiredBy[0] === username) return "green";
    if (item.desiredBy && item.desiredBy.includes(username)) return "yellow";
    return "white";
  };

  const [filter, setFilter] = useState<string>("all");
  const [expandedItem, setExpandedItem] = useState<number | null>(null);
  const [filteredItems, setFilteredItems] = useState<Item[]>([]);

  useEffect(() => {
    const applyFilter = () => {
      if (items && items.filter)
        setFilteredItems(items.filter((item) => {
          const bgColor = getItemBackgroundColor(item);
          return filter === "all" || bgColor === filter;
        }));
    };
    applyFilter();
  }, [items, filter]);

  const handleItemClick = (itemCode: number) => {
    setExpandedItem(expandedItem === itemCode ? null : itemCode);
  };

  const handleButtonClick = async (item: Item) => {
    try {
      let updatedItem = { ...item };
      if (item.takenBy === username) {
        updatedItem.takenBy = null;
      } else if (item.desiredBy && item.desiredBy[0] === username) {
        updatedItem.takenBy = username;
        updatedItem.desiredBy = updatedItem.desiredBy.filter(user => user !== username);
      } else if (item.desiredBy.includes(username)) {
        updatedItem.desiredBy = updatedItem.desiredBy.filter(user => user !== username);
      } else {
        updatedItem.desiredBy.push(username);
      }

      const response = await axios.patch(`http://localhost:3000/asset/${item.id}`, updatedItem);
      setItems((prevItems) => {
        const newItems = [...prevItems];
        return newItems.map((i) => (i.id === item.id ? response.data : i));
      });
      toast("Item updated successfully");
    } catch (error) {
      toast("Failed to update item");
    }
  };

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
          <IonTitle>Imprumuturi</IonTitle>
          {labelOnline ? (
            <IonTitle>ONLINE</IonTitle>
          ) : (
            <IonTitle>OFFLINE</IonTitle>
          )}
        </IonToolbar>
      </IonHeader>
      <IonContent fullscreen>
        <div className="filter-buttons">
          <button className={`filter-button ${filter === "all" ? "active" : ""}`} onClick={() => setFilter("all")} style={{ color: "black" }}>All</button>
          <button className={`filter-button ${filter === "red" ? "active" : ""}`} onClick={() => setFilter("red")} style={{ color: "red" }}>Red</button>
          <button className={`filter-button ${filter === "green" ? "active" : ""}`} onClick={() => setFilter("green")} style={{ color: "green" }}>Green</button>
          <button className={`filter-button ${filter === "yellow" ? "active" : ""}`} onClick={() => setFilter("yellow")} style={{ color: "yellow" }}>Yellow</button>
          <button className={`filter-button ${filter === "white" ? "active" : ""}`} onClick={() => setFilter("white")} style={{ color: "white" }}>White</button>
        </div>
        <div className="item-list">
          {Array.isArray(filteredItems) && filteredItems.map((item) => (
            <div
              key={item.id}
              className="item"
              style={{ backgroundColor: getItemBackgroundColor(item), color: "black" }}
              onClick={() => handleItemClick(item.id)}
            >
              <div className="item-name">{item.name}</div>
              {expandedItem === item.id && (
                <div className="item-details">
                  <div>Desired By: {item.desiredBy.join(", ")}</div>
                  <button className="item-button" onClick={() => handleButtonClick(item)}>
                    {item.takenBy === username && "Return"}
                    {item.desiredBy[0] === username && "Take"}
                    {item.desiredBy.includes(username) && item.desiredBy[0] !== username && "Remove request"}
                    {!item.desiredBy.includes(username) && !(item.takenBy === username) && "Add request"}
                  </button>
                </div>
              )}
            </div>
          ))}
        </div>
      </IonContent>
      <ToastContainer />
    </IonPage>
  );
};

export default Home;
