import { MouseEvent, useState } from 'react';
import { Child, Signup, AgeGroup, RaceDistance } from './Domain.ts'
import './Add.css'
import $ from 'jquery'
import { AddSignup } from './rest/rest.ts';

export const Add = (props: any) => {
    const [hidden, setHidden] = useState(true);
    const open = (e: MouseEvent) => {
        e.preventDefault();
        setHidden(false);
    }
    const add = (e: MouseEvent) => {
        e.preventDefault();
        const form = $(e.target).parent().siblings();
        const child: Child = {
            id: form.find('#cid').val() as string
        };
        const signup: Signup = {
            child: child,
            ageGroup: Object.keys(AgeGroup)[Object.values(AgeGroup).indexOf(form.find('#age').val() as AgeGroup)],
            raceDistance: Object.keys(RaceDistance)[Object.values(RaceDistance).indexOf(form.find('#race').val() as RaceDistance)],
        }
        AddSignup(signup)
            .then(text => {
                props.setCount(Date.now());
            })
            .catch(_ => {
                alert('Could not add');
            })
        setHidden(true);
    }
    const close = (e : MouseEvent) => {
        e.preventDefault();
        setHidden(true);
    }
    return (
        <div className='box'>
            <div className='head'>
                <h1>Contest Signups</h1>
                <div className='add'>
                    <a href="#" onClick={open}>+</a>
                </div>
            </div>
            <div className={hidden ? 'hidden' : 'active'}>
                <div className='closehead'>
                    <div className='close'>
                        <a href="#" onClick={close}>X</a>
                    </div>
                </div>
                <div className='row'>
                    <span>Child id:</span>
                    <input id='cid'></input>
                </div>
                <div className='row'>
                    <span>Age Group:</span>
                    <input id='age'></input>
                </div>
                <div className='row'>
                    <span>Race Distance:</span>
                    <input id='race'></input>
                </div>
                <div className='edit'>
                    <a href="#" onClick={add}>Add</a>
                </div>
            </div>
        </div>
    )
}