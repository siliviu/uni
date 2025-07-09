 import { createAnimation } from '@ionic/react';

export const enterAnimation = (baseEl: HTMLElement) => {

  const backdropAnimation = createAnimation()
    .addElement(document.querySelector('ion-backdrop')!)
    .fromTo('opacity', '0', 'var(--backdrop-opacity)');

  const wrapperAnimation = createAnimation()
    .addElement(document.querySelector('.loading-wrapper')!)
    .keyframes([
      { offset: 0, opacity: '0', transform: 'scale(0.8)' },
      { offset: 1, opacity: '1', transform: 'scale(1)' },
    ]);

  return createAnimation()
    .addElement(baseEl)
    .easing('ease-out')
    .duration(2000)
    .addAnimation([backdropAnimation, wrapperAnimation]);
};
