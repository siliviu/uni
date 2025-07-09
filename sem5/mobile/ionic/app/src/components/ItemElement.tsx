import React, { memo } from 'react';
import { IonIcon, IonItem, IonLabel } from '@ionic/react';
import { getLogger } from '../core';
import { Item } from '../model/Item';
import './icon.css'
import { checkmarkOutline, closeOutline } from 'ionicons/icons'

const log = getLogger('Item');

interface ItemPropsExt  {
  id: string,
  title: string,
  author: string,
  read: boolean,
  onEdit: (id?: string) => void;
}

const ItemElement: React.FC<ItemPropsExt> = ({ id, title, author, read, onEdit }) => {
  return (
    <IonItem onClick={() => onEdit(id)}>
      <IonIcon aria-hidden="true" slot="start" icon={read ? checkmarkOutline : closeOutline} className={read ? "check" : "close"} />
      <IonLabel>{title}, {author}</IonLabel>
    </IonItem>
  );
};

export default memo(ItemElement);
