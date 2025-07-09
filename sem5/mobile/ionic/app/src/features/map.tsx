import { GoogleMap } from '@capacitor/google-maps';
import { useEffect, useRef, useState } from 'react';
import { mapsApiKey } from '../api/mapsApiKey';

interface MyMapProps {
  lat: number;
  lng: number;
  setSelectedLocation: any;
  onMapClick: (e: any) => void;
  onMarkerClick: (e: any) => void;
}

export const Map: React.FC<MyMapProps> = ({ lat, lng, setSelectedLocation, onMapClick, onMarkerClick }) => {
  const mapRef = useRef<HTMLElement>(null);
  const marker = useRef<string>();
  const mapCreatedRef = useRef(false);

  useEffect(() => {
    console.log("USE EFFECT MAP");
    if (mapCreatedRef.current) return;
    mapCreatedRef.current = true;
    createMap();

    return () => {
      googleMap?.removeAllMapListeners();
    };
  }, []);

  let googleMap: GoogleMap | null = null;

  const createMap = async () => {
    if (!mapRef.current) {
      return;
    }

    googleMap = await GoogleMap.create({
      id: 'my-cool-map',
      element: mapRef.current,
      apiKey: mapsApiKey,
      config: {
        center: { lat, lng },
        zoom: 8,
      },
    });

    const initialMarker = await googleMap.addMarker({ coordinate: { lat, lng }, title: 'Current location' });
    marker.current = initialMarker;
    console.log("IN " + initialMarker);
    googleMap.setOnMapClickListener(async ({ latitude, longitude }) => {
      setSelectedLocation({ lat: latitude, lng: longitude });
      console.log("OLD " + marker);
      if (marker) {
        await googleMap!.removeMarker(marker.current!);
      }
      const newMarker = await googleMap!.addMarker({
        coordinate: { lat: latitude, lng: longitude },
        title: 'New location',
      });
      marker.current = newMarker;
      console.log("NEW " + marker);
      onMapClick({ latitude, longitude });
    });

    googleMap.setOnMarkerClickListener(({ markerId, latitude, longitude }) => {
      onMarkerClick({ markerId, latitude, longitude });
    });
  };

  return (
    <div className="component-wrapper">
      <capacitor-google-map
        ref={mapRef}
        style={{
          display: 'block',
          width: 300,
          height: 400,
        }}
      ></capacitor-google-map>
    </div>
  );
};
