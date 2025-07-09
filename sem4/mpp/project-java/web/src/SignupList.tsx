import { SignupDiv } from './Signup.tsx'
import './SignupList.css'

export const SignupList = (props: any) => {
    const elements: Array<JSX.Element> = [];
    for (let element of props.signups)
        elements.push(<SignupDiv signup={element} key={element.id}></SignupDiv>)
    return (
        <div className='list'>
            {elements}
        </div>)
}