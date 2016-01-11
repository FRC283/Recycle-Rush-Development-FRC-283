#include "OperatorButton.h"

// Constructor for Joystick Button
/* OperatorButton::OperatorButton(Joystick *js, uint32_t number) :
	m_js(js)
	, m_buttonNum(number)
	, m_lastState(false)
{
}
 */
 OperatorButton::OperatorButton(uint32_t js, uint32_t number) :
	m_buttonNum(number)
	, m_lastState(false)
{
	m_js = Joystick::GetStickForPort(js);
}

// Constructor for button from DigitalIO Board
/* OperatorButton::OperatorButton(uint32_t number) :
	m_js(NULL)
	, m_buttonNum(number)
	, m_lastState(false)
{
}
 */
OperatorButton::~OperatorButton()
{
}

OperatorButton::ButtonState OperatorButton::Get(void)
{
	uint16_t digitals;
	bool curr_state;
	ButtonState state;

	if (m_js) {
		curr_state = m_js->GetRawButton(m_buttonNum);
	}
	state = DetermineState(curr_state, m_lastState);
	m_lastState = curr_state;
	return state;
}

bool OperatorButton::GetBool(void)
{

	if (m_js) {
		return m_js->GetRawButton(m_buttonNum);
	}

	return (1 << (m_buttonNum-1));
}

OperatorButton::ButtonState OperatorButton::DetermineState(bool current, bool previous)
{
	if (current) {
		if (previous) {
			return kPressed;
		} else {
			return kJustPressed;
		}
	} else {
		if (previous) {
			return kJustReleased;
		} else {
			return kReleased;
		}
	}
}
