import { useState, useEffect } from 'react'
import { SignupList } from './SignupList.tsx'
import { Add } from './Add.tsx'
import { GetSignups } from './rest/rest.ts'
import './App.css'

export default function App() {
  const [signups, setSignups] = useState([]);
  const [count, setCount] = useState(1);
  useEffect(() => {
    GetSignups().then(signups => {
      setSignups(signups);
    })
  }, [count]);
  return (<>
    <Add setCount={setCount}></Add>
    <SignupList signups={signups} key={count.toString()}></SignupList>
  </>)
}