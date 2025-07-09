import React, { useContext, useEffect, useRef, useState } from 'react';
import { RouteComponentProps } from 'react-router';
import {
  createAnimation,
  IonButton,
  IonContent,
  IonFab,
  IonFabButton,
  IonHeader,
  IonIcon,
  IonInfiniteScroll,
  IonInfiniteScrollContent,
  IonItem,
  IonList, IonLoading,
  IonPage,
  IonSearchbar,
  IonSelect,
  IonSelectOption,
  IonTitle,
  IonToolbar
} from '@ionic/react';
import { add, enter } from 'ionicons/icons';
import ItemElement from '../ItemElement';
import { getLogger } from '../../core';
import { ItemContext } from '../../features/ItemProvider';
import { useNetworkStatus } from '../../features/NetworkStatus';
import { AuthContext } from '../../features/AuthProvider';
import { backOnline } from '../../storage/books';
import { enterAnimation, leaveAnimation } from '../../features/customAnimation';

const log = getLogger('ItemList');

const ItemList: React.FC<RouteComponentProps> = ({ history }) => {
  const { items, fetching, fetchingError, setTitle, setRead, clearFilter, nextPage } = useContext(ItemContext);
  const { token } = useContext(AuthContext);
  const { networkStatus, apiStatus } = useNetworkStatus(() => backOnline(token, items, clearFilter));

  const { logout } = useContext(AuthContext);

  const fabRef = useRef<HTMLIonFabElement>(null);

  useEffect(() => {
    const pulsate = createAnimation()
      .addElement(fabRef.current!)
      .duration(1250)
      .iterations(Infinity)
      .fromTo('transform', 'scale(1)', 'scale(1.25)');
    pulsate.play();
  }, []);
  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
          <IonTitle>Read list</IonTitle>
        </IonToolbar>
        <IonButton onClick={logout}> Logout</IonButton>
        <IonButton> Network: {networkStatus}</IonButton>
        <IonButton> API: {apiStatus}</IonButton>
        <IonButton onClick={clearFilter}> Clear Filter</IonButton>
        <IonSelect onIonChange={e => setRead(e.detail.value)} placeholder="Read Filter">
          <IonSelectOption value={true}>Read</IonSelectOption>
          <IonSelectOption value={false}>Not read</IonSelectOption>
        </IonSelect>
        <IonSearchbar onIonChange={e => setTitle(e.detail.value!)}></IonSearchbar>
      </IonHeader>
      <IonContent>
        <IonLoading isOpen={fetching} enterAnimation={enterAnimation}/>
          {items &&
          <IonList>
            {items.length == 0 ? <IonItem>No books</IonItem> : items.map(({ _id, title, author, read }: any) =>
              <ItemElement key={_id} id={_id} title={title} author={author} read={read} onEdit={id => history.push(`/item/${id}`)} />)}
            <IonInfiniteScroll
              onIonInfinite={async e => {
              await nextPage();
              e.target.complete();
            }
            }>
              <IonInfiniteScrollContent
                loadingText="Loading books...">
              </IonInfiniteScrollContent>
            </IonInfiniteScroll>
          </IonList>
          }
          {/* {fetchingError && (
          <div>{fetchingError.message || 'Failed to fetch items'}</div>
        )} */}
        <IonFab vertical="bottom" horizontal="end" slot="fixed" ref={fabRef}>
          <IonFabButton onClick={() => history.push('/item')}>
            <IonIcon icon={add} />
          </IonFabButton>
        </IonFab>
      </IonContent>
    </IonPage>
  );
};

export default ItemList;
