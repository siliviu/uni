import { Camera, CameraResultType, CameraSource } from '@capacitor/camera';
import { Directory, Filesystem } from '@capacitor/filesystem';
import { useCallback, useState } from 'react';


export interface MyPhoto {
    filepath: string;
    webviewPath?: string;
}

export function useCamera() {
    const [photo, setPhoto] = useState<MyPhoto>();
    const getPhoto = () => Camera.getPhoto({
        resultType: CameraResultType.Base64,
        source: CameraSource.Camera,
        quality: 100,
        allowEditing: true
    });

    const writeFile = useCallback<(path: string, data: string) => Promise<any>>(
        (path, data) => {
            return Filesystem.writeFile({
                path,
                data,
                directory: Directory.Data,
            })
        }, []);

    async function takePhoto() {
        const { base64String } = await getPhoto();
        const filepath = new Date().getTime() + '.jpeg';
        // await writeFile(filepath, base64String!);
        const webviewPath = `data:image/jpeg;base64,${base64String}`
        const newPhoto = { filepath, webviewPath };
        setPhoto(newPhoto);
    }

    async function savePhoto(photo: MyPhoto) {
        await writeFile(photo.filepath, photo.webviewPath!);
    }

    return {
        takePhoto, photo, setPhoto, savePhoto
    };
}