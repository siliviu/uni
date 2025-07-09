import { MouseEventHandler, useEffect, useState } from 'react'
import './Signup.css'
import { Child, Signup, AgeGroup, RaceDistance } from './Domain.ts'
import { DeleteSignup, ModifySignup } from './rest/rest.ts'
import $ from 'jquery'

export const SignupDiv = (props: any) => {
    const [hidden, setHidden] = useState(false);
    const [editing, setEditing] = useState(false);
    const [signup, setSignup] = useState(props.signup);
    const [child, setChild] = useState(signup.child);
    const [key, setKey] = useState(0);
    if (!signup.child)
        return <div></div>;
    const hide = (e: any) => {
        e.preventDefault();
        DeleteSignup(signup)
            .then(_ => { setHidden(true); })
            .catch(_ => alert('Could not delete'));
    }
    const edit = (e: any) => {
        e.preventDefault();
        setEditing(true);
    }
    const save = (e: any) => {
        e.preventDefault();
        const form = $(e.target).parent().siblings();
        const child: Child = {
            id: form.find('#cid').val() as string
        };
        const newsignup: Signup = {
            child: child,
            ageGroup: Object.keys(AgeGroup)[Object.values(AgeGroup).indexOf(form.find('#age').val() as AgeGroup)],
            raceDistance: Object.keys(RaceDistance)[Object.values(RaceDistance).indexOf(form.find('#race').val() as RaceDistance)],
        }
        console.log(newsignup);
        setEditing(false);
        ModifySignup(signup.id!, newsignup)
            .then(text => {
                const s: Signup = text;
                setChild(s.child);
                setSignup(s);
            })
            .catch(_ => {
                alert('Could not edit');
            })
            .then(() => {
                setKey(Date.now());
            });
    }
    if (!hidden)
        return (
            <div className='container' key={key}>
                <div className='header'>Id: {signup.id}
                    <div className='delete'>
                        <a href="#" onClick={hide}>X</a>
                    </div>
                </div>
                <div className='row nested'> Child:
                    <div className='row'>
                        <span>Id:</span>
                        <input defaultValue={child.id} readOnly={!editing} id='cid'></input>
                    </div>
                    <div className='row'>
                        <span>Name:</span>
                        <input defaultValue={child.name} readOnly={true} id='cname'></input>
                    </div>
                    <div className='row'>
                        <span>Age:</span>
                        <input defaultValue={child.age} readOnly={true} id='cage'></input>
                    </div>
                </div>
                <div className='row'>
                    <span>Age Group:</span>
                    <input defaultValue={AgeGroup[signup.ageGroup as keyof typeof AgeGroup]} readOnly={!editing} id='age'></input>
                </div>
                <div className='row'>
                    <span>Race Distance:</span>
                    <input defaultValue={RaceDistance[signup.raceDistance as keyof typeof RaceDistance]} readOnly={!editing} id='race'></input>
                </div>
                <div className='edit'>
                    {editing ?
                        <a href="#" onClick={save}>Save</a> : <a href="#" onClick={edit}>Edit</a>}
                </div>
            </div>
        )
    return <></>
}