import React, { useCallback, useContext, useEffect, useRef, useState } from 'react';
import {
  IonButton,
  IonButtons,
  IonCheckbox,
  IonCol,
  IonContent,
  IonGrid,
  IonHeader,
  IonImg,
  IonInput,
  IonLabel,
  IonLoading,
  IonPage,
  IonRow,
  IonTitle,
  IonToolbar
} from '@ionic/react';
import { getLogger } from '../core';
import { ItemContext } from '../features/ItemProvider';
import { RouteComponentProps } from 'react-router';
import { Item } from '../model/Item';
import './item.css'
import { getItem } from '../api/itemApi';
import { AuthContext } from '../features/AuthProvider';
import { getBookFromStorage } from '../storage/books';
import { useCamera } from '../features/useCamera';
import { useLocation } from '../features/useLocation';
import { Map } from '../features/map'

const log = getLogger('ItemEdit');

interface ItemEditProps extends RouteComponentProps<{
  id?: string;
}> { }

const ItemEdit: React.FC<ItemEditProps> = ({ history, match }) => {
  const myLocation = useLocation();
  const count = useRef(0);
  const [selectedLocation, setSelectedLocation] = useState<{ lat: number, lng: number } | null>(null);
  const { latitude: lat, longitude: lng } = myLocation.position?.coords || {}
  const { token } = useContext(AuthContext);
  const { saving, savingError, saveItem, clearFilter } = useContext(ItemContext);
  const { photo, setPhoto, takePhoto, savePhoto } = useCamera();
  const [read, setRead] = useState<boolean>(false);
  const [title, setTitle] = useState<string>();
  const [author, setAuthor] = useState<string>();
  const [launched, setLaunched] = useState<Date>();
  const [price, setPrice] = useState<number>();
  const [item, setItem] = useState<Item>();
  useEffect(() => {
    if (count.current != 0)
      return;
    count.current = count.current + 1;
    const routeId = match.params.id || '';
    getItem(routeId, token)
      .catch(() => {
        return getBookFromStorage(routeId);
      })
      .then(item => {
        setItem(item);
        if (item) {
          setTitle(item.title);
          setRead(item.read);
          setAuthor(item.author);
          setLaunched(item.launched);
          setPrice(item.price);
          setSelectedLocation({ lat: item.lat, lng: item.lng })
          setPhoto({
            filepath: 'haha.jpeg',
            webviewPath: item.image
          });
        }
      })
  }, [match.params.id]);
  const handleSave = () => {
    const editedItem = {
      _id: item ? item._id : null,
      title: title!,
      author: author!,
      launched: launched!,
      price: price!,
      read: read == undefined ? false : read,
      image: photo ? photo.webviewPath : null,
      lat: selectedLocation ? selectedLocation.lat : null,
      lng: selectedLocation ? selectedLocation.lng : null
    };
    saveItem && saveItem(editedItem).then(() => { history.goBack(); window });
  };
  log('render');
  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
          <IonTitle>Edit</IonTitle>
          <IonButtons slot="end">
            <IonButton onClick={handleSave}>
              Save
            </IonButton>
          </IonButtons>
        </IonToolbar>
      </IonHeader>
      <IonContent>
        <IonGrid>
          <IonRow>
            <IonCol>
              <IonLabel className="field-label">Title: </IonLabel>
              <IonInput value={title} onIonChange={e => {
                setTitle(e.detail.value || '');
              }} />
            </IonCol>
          </IonRow>
          <IonRow>
            <IonCol>
              <IonLabel className="field-label">Author: </IonLabel>
              <IonInput value={author} onIonChange={e => setAuthor(e.detail.value || '')} />
            </IonCol>
          </IonRow>
          <IonRow>
            <IonCol>
              <IonLabel className="field-label">Launched: </IonLabel>
              <IonInput value={launched as unknown as string} readonly={true} />
            </IonCol>
          </IonRow>
          <IonRow>
            <IonCol>
              <IonLabel className="field-label">Price: </IonLabel>
              <IonInput value={price} onIonChange={e => setPrice(Number(e.detail.value))} />
            </IonCol>
          </IonRow>
          <IonRow>
            <IonCol>
              <IonLabel className="field-label">Read: </IonLabel>
              <IonCheckbox checked={read} onIonChange={e => setRead(e.detail.checked)}></IonCheckbox>
            </IonCol>
          </IonRow>
          <IonRow>
            <IonCol>
              <IonButton onClick={() => takePhoto()}>Change photo</IonButton>
              {photo && <IonButton onClick={() => { console.log(photo); savePhoto(photo); }}>Save Photo</IonButton>}
              {photo && <IonImg className='img' src={photo.webviewPath} />}
            </IonCol>
          </IonRow>
          <IonRow>
            <IonCol>
              <IonLabel>Current Location is {lat && lng ? `latitude: ${lat}, longitude: ${lng}` : "Unavailable"}</IonLabel>
            </IonCol>

          </IonRow>
          <IonRow>
            <IonCol>
              {selectedLocation && <IonLabel>Selected Location is {selectedLocation && selectedLocation.lat ? `latitude: ${selectedLocation.lat}, longitude: ${selectedLocation.lng}` : "null"}</IonLabel>}
            </IonCol>
          </IonRow>
          {lat && lng &&
            <IonRow>
              <IonCol>
                <Map
                  lat={selectedLocation && selectedLocation.lat ? selectedLocation.lat : lat}
                  lng={selectedLocation && selectedLocation.lng ? selectedLocation.lng : lng}
                  setSelectedLocation={setSelectedLocation}
                  onMapClick={() => log('onMap')}
                  onMarkerClick={() => log('onMarker')}
                />
              </IonCol>
            </IonRow>
          }
        </IonGrid>
        <IonLoading isOpen={saving} />
        {savingError && (
          <div>{savingError.message || 'Failed to save item'}</div>
        )}
      </IonContent>
    </IonPage >
  );
};

export default ItemEdit;
