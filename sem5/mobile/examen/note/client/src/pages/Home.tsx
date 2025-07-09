import {
  IonButton,
  IonContent,
  IonHeader,
  IonInfiniteScroll,
  IonInfiniteScrollContent,
  IonItem,
  IonLabel,
  IonList,
  IonLoading,
  IonPage,
  IonTitle,
  IonToolbar,
  IonAlert,
} from "@ionic/react";
import "./Home.css";
import { useEffect, useRef, useState } from "react";
import { useConnection } from "../notifications/connection";
import { toast } from "react-toastify";
import { ToastContainer } from "react-toastify";
import "react-toastify/dist/ReactToastify.css";
import { Note, NoteResponse, getNotes, getCachedNotes, cacheNotes, deleteNote, cacheDeletedNotes, getCachedDeletedNotes } from "../data/item";
import { connect } from "../notifications/notifications";

const Home: React.FC = () => {
  const first = useRef(true);
  const [loading, setLoading] = useState(false);
  const [notes, setNotes] = useState<Note[]>([]);
  const [deletedNotes, setDeletedNotes] = useState<Note[]>([]);
  const [currentPage, setCurrentPage] = useState(0);
  const [error, setError] = useState(false);
  const [showAlert, setShowAlert] = useState(false);
  const [noteToDelete, setNoteToDelete] = useState<Note | null>(null);

  useEffect(() => {
    if (first.current) {
      first.current = false;
      fetchNotes();
    }
    const webSocket = connect((event, note) => {
      if (event === "inserted") {
        setNotes((prevNotes) => {
          if (prevNotes.some((n) => n.id === note.id)) {
            return prevNotes;
          }
          return [note, ...prevNotes]
        });
      } else if (event === "deleted") {
        setNotes((prevNotes) => prevNotes.filter((n) => n.id !== note.id));
      }
      toast.info(`Note ${note.id} ${event} successfully`);
    });
    return () => {
      webSocket.close();
    };
  }, []);

  useEffect(() => {
    const interval = setInterval(() => {
      retryFailedDeletions();
    }, 20000);
    return () => clearInterval(interval);
  }, [deletedNotes]);

  const fetchNotes = async () => {
    setLoading(true);
    try {
      const response: NoteResponse = await getNotes(currentPage);
      setNotes((prevNotes) => {
        const updatedNotes = [...prevNotes];
        response.notes.forEach((newNote) => {
          const index = updatedNotes.findIndex((note) => note.id === newNote.id);
          if (index !== -1) {
            updatedNotes[index] = newNote;
          } else {
            updatedNotes.push(newNote);
          }
        });
        return updatedNotes;
      });
      cacheNotes([...notes, ...response.notes]);
      setCurrentPage((prevPage) => prevPage + 1);
    } catch {
      setNotes(() => getCachedNotes());
      setError(true);
      toast.error("Error fetching notes");
    }
    setLoading(false);
  };

  const handleDelete = (note: Note) => {
    setNoteToDelete(note);
    setShowAlert(true);
  };

  const confirmDelete = async () => {
    if (noteToDelete) {
      try {
        await deleteNote(noteToDelete.id);
        setNotes((prevNotes) => prevNotes.filter((note) => note.id !== noteToDelete.id));
        setDeletedNotes((prevNotes) => prevNotes.filter((note) => note.id !== noteToDelete.id));
        toast.success("Note deleted successfully");
      } catch {
        setDeletedNotes([...deletedNotes, noteToDelete]);
        toast.error("Failed to delete note. Will retry.");
      }
      setNoteToDelete(null);
      setShowAlert(false);
    }
  };

  const retryFailedDeletions = async () => {
    const updatedDeletedNotes = [];
    console.log('retrying');
    console.log(deletedNotes);
    for (const note of deletedNotes) {
      try {
        await deleteNote(note.id);
        setNotes((prevNotes) => prevNotes.filter((n) => n.id !== note.id));
        toast.success(`Note ${note.id} deleted successfully`);
      } catch {
        updatedDeletedNotes.push(note);
      }
    }
    setDeletedNotes(updatedDeletedNotes);
    console.log(deletedNotes);
    cacheDeletedNotes(updatedDeletedNotes);
  };

  //PT HANDLE ONLINE/OFFLINE
  const [isOnline, setIsOnline] = useConnection();
  const [labelOnline, setLabelOnline] = useState(false);
  useEffect(() => {
    if (!isOnline) {
      setLabelOnline(false);
    } else {
      setLabelOnline(true);
    }
  }, [isOnline]);

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
          <IonTitle>Notes</IonTitle>
          {labelOnline ? (
            <IonTitle>ONLINE</IonTitle>
          ) : (
            <IonTitle>OFFLINE</IonTitle>
          )}
        </IonToolbar>
      </IonHeader>
      <IonContent fullscreen>
        {/* {error && (
          <IonButton onClick={fetchNotes}>
            <IonLabel>Retry</IonLabel>
          </IonButton>
        )} */}
        <IonList>
          {notes.map((note) => (
            <IonItem key={note.id} color={deletedNotes.some((n) => n.id === note.id) ? "warning" : ""}>
              {note.text} - {new Date(note.date).toLocaleString()}
              <IonButton slot="end" color="danger" onClick={() => handleDelete(note)}>
                Delete
              </IonButton>
            </IonItem>
          ))}
          <IonInfiniteScroll
            onIonInfinite={async (event) => {
              await fetchNotes();
              (event.target as HTMLIonInfiniteScrollElement).complete();
            }}
          >
            <IonInfiniteScrollContent loadingText="Loading more notes..."></IonInfiniteScrollContent>
          </IonInfiniteScroll>
        </IonList>
        {/* {loading && <IonLoading isOpen={true} message="Loading notes..." />} */}
        <IonAlert
          isOpen={showAlert}
          onDidDismiss={() => setShowAlert(false)}
          header={"Confirm Delete"}
          message={"Are you sure you want to delete this note?"}
          buttons={[
            {
              text: "Cancel",
              role: "cancel",
              cssClass: "secondary",
              handler: () => {
                setShowAlert(false);
              },
            },
            {
              text: "Delete",
              handler: confirmDelete,
            },
          ]}
        />
      </IonContent>
      <ToastContainer containerId={"id"} />
    </IonPage>
  );
};

export default Home;
