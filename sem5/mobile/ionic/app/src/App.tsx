import { Redirect, Route } from 'react-router-dom';
import { IonApp, IonRouterOutlet, setupIonicReact } from '@ionic/react';
import { IonReactRouter } from '@ionic/react-router';

/* Core CSS required for Ionic components to work properly */
import '@ionic/react/css/core.css';

/* Basic CSS for apps built with Ionic */
import '@ionic/react/css/normalize.css';
import '@ionic/react/css/structure.css';
import '@ionic/react/css/typography.css';

/* Optional CSS utils that can be commented out */
import '@ionic/react/css/padding.css';
import '@ionic/react/css/float-elements.css';
import '@ionic/react/css/text-alignment.css';
import '@ionic/react/css/text-transformation.css';
import '@ionic/react/css/flex-utils.css';
import '@ionic/react/css/display.css';

/**
 * Ionic Dark Mode
 * -----------------------------------------------------
 * For more info, please see:
 * https://ionicframework.com/docs/theming/dark-mode
 */

/* import '@ionic/react/css/palettes/dark.always.css'; */
/* import '@ionic/react/css/palettes/dark.class.css'; */
import '@ionic/react/css/palettes/dark.system.css';

/* Theme variables */
import './theme/variables.css';
import { ItemList } from './components';
import { ItemProvider } from './features/ItemProvider';
import ItemEdit from './components/ItemEdit';
import { AuthProvider } from './features/AuthProvider';
import { Login } from './components/Login/login';
import { PrivateRoute } from './core/PrivateRoute';

setupIonicReact();

const App: React.FC = () => (
  <IonApp>
    <AuthProvider>
      <ItemProvider>
        <IonReactRouter>
          <IonRouterOutlet>
            <Route path="/login" exact={true} component={Login} />
            <PrivateRoute path="/items" component={ItemList} exact={true} />
            <PrivateRoute path="/item" component={ItemEdit} exact={true} />
            <PrivateRoute path="/item/:id" component={ItemEdit} exact={true} />
            <Route exact path="/" render={() => <Redirect to="/items" />} />
          </IonRouterOutlet>
        </IonReactRouter>
      </ItemProvider>
    </AuthProvider>
  </IonApp>
);

export default App;
