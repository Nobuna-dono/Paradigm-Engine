#ifndef _NATIVEINPUTENUMS_DIRECTINPUT_H_
#define _NATIVEINPUTENUMS_DIRECTINPUT_H_


namespace ParadigmEngine
{
	namespace NativeInterface
	{
		namespace Input
		{

		#define _NAT_CASE_KEY_TO_DIKEY(X) \
		case CONCATENATE(ENativeKeyCode::,X):\
			return CONCATENATE(ENativeKeycode_DirectInput::NAT_DIK_, X);

			enum ENativeKeycode_DirectInput
			{
				NAT_DIK_None = 0x00,
				NAT_DIK_Escape = 0x01,
				NAT_DIK_Return = 0x1C,    /* Enter on main keyboard */
				NAT_DIK_Space = 0x39,
				NAT_DIK_Backspace = 0x0E,    /* backspace */
				NAT_DIK_Tab = 0x0F,

				NAT_DIK_Alpha0 = 0x0B,
				NAT_DIK_Alpha1 = 0x02,
				NAT_DIK_Alpha2 = 0x03,
				NAT_DIK_Alpha3 = 0x04,
				NAT_DIK_Alpha4 = 0x05,
				NAT_DIK_Alpha5 = 0x06,
				NAT_DIK_Alpha6 = 0x07,
				NAT_DIK_Alpha7 = 0x08,
				NAT_DIK_Alpha8 = 0x09,
				NAT_DIK_Alpha9 = 0x0A,

				NAT_DIK_Keypad0 = 0x52,
				NAT_DIK_Keypad1 = 0x4F,
				NAT_DIK_Keypad2 = 0x50,
				NAT_DIK_Keypad3 = 0x51,
				NAT_DIK_Keypad4 = 0x4B,
				NAT_DIK_Keypad5 = 0x4C,
				NAT_DIK_Keypad6 = 0x4D,
				NAT_DIK_Keypad7 = 0x47,
				NAT_DIK_Keypad8 = 0x48,
				NAT_DIK_Keypad9 = 0x49,

				NAT_DIK_KeypadPeriod = 0x34,    /* . on main keyboard */
				NAT_DIK_KeypadSlash = 0x35,    /* / on main keyboard */
				NAT_DIK_KeypadDivide = 0xB5,    /* / on main keyboard */
				NAT_DIK_KeypadMultiply = 0x37,    /* * on numeric keypad */
				NAT_DIK_KeypadMinus = 0x4A,    /* - on numeric keypad */
				NAT_DIK_KeypadAdd = 0x4E,    /* + on numeric keypad */
				NAT_DIK_KeypadEnter = 0x9C,    /* enter on numeric keypad */
				NAT_DIK_KeypadDecimal = 0x53,    /* . on numeric keypad */
				NAT_DIK_KeypadNumLock = 0x45,

				NAT_DIK_Up = 0xC8,    /* UpArrow on arrow keypad */
				NAT_DIK_Left = 0xCB,    /* LeftArrow on arrow keypad */
				NAT_DIK_Right = 0xCD,    /* RightArrow on arrow keypad */
				NAT_DIK_Down = 0xD0,    /* DownArrow on arrow keypad */

				NAT_DIK_F1 = 0x3B,
				NAT_DIK_F2 = 0x3C,
				NAT_DIK_F3 = 0x3D,
				NAT_DIK_F4 = 0x3E,
				NAT_DIK_F5 = 0x3F,
				NAT_DIK_F6 = 0x40,
				NAT_DIK_F7 = 0x41,
				NAT_DIK_F8 = 0x42,
				NAT_DIK_F9 = 0x43,
				NAT_DIK_F10 = 0x44,
				NAT_DIK_F11 = 0x57,
				NAT_DIK_F12 = 0x58,

				NAT_DIK_Q = 0x10,
				NAT_DIK_W = 0x11,
				NAT_DIK_E = 0x12,
				NAT_DIK_R = 0x13,
				NAT_DIK_T = 0x14,
				NAT_DIK_Y = 0x15,
				NAT_DIK_U = 0x16,
				NAT_DIK_I = 0x17,
				NAT_DIK_O = 0x18,
				NAT_DIK_P = 0x19,
				NAT_DIK_A = 0x1E,
				NAT_DIK_S = 0x1F,
				NAT_DIK_D = 0x20,
				NAT_DIK_F = 0x21,
				NAT_DIK_G = 0x22,
				NAT_DIK_H = 0x23,
				NAT_DIK_J = 0x24,
				NAT_DIK_K = 0x25,
				NAT_DIK_L = 0x26,
				NAT_DIK_Z = 0x2C,
				NAT_DIK_X = 0x2D,
				NAT_DIK_C = 0x2E,
				NAT_DIK_V = 0x2F,
				NAT_DIK_B = 0x30,
				NAT_DIK_N = 0x31,
				NAT_DIK_M = 0x32,

				NAT_DIK_CapsLock = 0x3A,
				NAT_DIK_LeftAlt = 0x38,    /* left Alt */
				NAT_DIK_RightAlt = 0xB8,    /* right Alt */
				NAT_DIK_LeftShift = 0x2A,
				NAT_DIK_RightShift = 0x36,
				NAT_DIK_LeftControl = 0x1D,
				NAT_DIK_RightControl = 0x9D,
				NAT_DIK_LeftBracket = 0x1A,
				NAT_DIK_RightBracket = 0x1B,
				NAT_DIK_LeftWindows = 0xDB,    /* Left Windows key */
				NAT_DIK_RightWindows = 0xDC,    /* Right Windows key */

				NAT_DIK_Add = 0x4E,    /* - on main keyboard */
				NAT_DIK_Minus = 0x0C,    /* - on main keyboard */
				NAT_DIK_Equals = 0x0D,

				NAT_DIK_Insert = 0xD2,    /* Insert on arrow keypad */
				NAT_DIK_Delete = 0xD3,    /* Delete on arrow keypad */
				NAT_DIK_Home = 0xC7,
				NAT_DIK_End = 0xCF,

				NAT_DIK_Power = 0xDE,    /* System Power */

				NAT_DIK_Last = 0xDF,
			};



			constexpr ENativeKeycode_DirectInput ToDirectInputKeyCode(ENativeKeyCode _key)
			{
				switch (_key)
				{
					_NAT_CASE_KEY_TO_DIKEY(Escape);
					_NAT_CASE_KEY_TO_DIKEY(Return);
					_NAT_CASE_KEY_TO_DIKEY(Space);
					_NAT_CASE_KEY_TO_DIKEY(Backspace);
					_NAT_CASE_KEY_TO_DIKEY(Tab);
					_NAT_CASE_KEY_TO_DIKEY(Alpha0); 
					_NAT_CASE_KEY_TO_DIKEY(Alpha1);		
					_NAT_CASE_KEY_TO_DIKEY(Alpha2); 
					_NAT_CASE_KEY_TO_DIKEY(Alpha3);
					_NAT_CASE_KEY_TO_DIKEY(Alpha4);		 
					_NAT_CASE_KEY_TO_DIKEY(Alpha5);		
					_NAT_CASE_KEY_TO_DIKEY(Alpha6);		 
					_NAT_CASE_KEY_TO_DIKEY(Alpha7);		
					_NAT_CASE_KEY_TO_DIKEY(Alpha8);		 
					_NAT_CASE_KEY_TO_DIKEY(Alpha9);		
					_NAT_CASE_KEY_TO_DIKEY(Keypad0);		 
					_NAT_CASE_KEY_TO_DIKEY(Keypad1);		
					_NAT_CASE_KEY_TO_DIKEY(Keypad2);		 
					_NAT_CASE_KEY_TO_DIKEY(Keypad3);		
					_NAT_CASE_KEY_TO_DIKEY(Keypad4);		 
					_NAT_CASE_KEY_TO_DIKEY(Keypad5);		
					_NAT_CASE_KEY_TO_DIKEY(Keypad6);		 
					_NAT_CASE_KEY_TO_DIKEY(Keypad7);		
					_NAT_CASE_KEY_TO_DIKEY(Keypad8);		 
					_NAT_CASE_KEY_TO_DIKEY(Keypad9);		
					_NAT_CASE_KEY_TO_DIKEY(KeypadPeriod);	 
					_NAT_CASE_KEY_TO_DIKEY(KeypadDivide);	
					_NAT_CASE_KEY_TO_DIKEY(KeypadSlash);	 
					_NAT_CASE_KEY_TO_DIKEY(KeypadMultiply);
					_NAT_CASE_KEY_TO_DIKEY(KeypadMinus);	
					_NAT_CASE_KEY_TO_DIKEY(KeypadAdd);		 
					_NAT_CASE_KEY_TO_DIKEY(KeypadEnter);					
					_NAT_CASE_KEY_TO_DIKEY(KeypadDecimal);					 
					_NAT_CASE_KEY_TO_DIKEY(KeypadNumLock);					
					_NAT_CASE_KEY_TO_DIKEY(Up);					 
					_NAT_CASE_KEY_TO_DIKEY(Down);					
					_NAT_CASE_KEY_TO_DIKEY(Left);					 
					_NAT_CASE_KEY_TO_DIKEY(Right);					
					_NAT_CASE_KEY_TO_DIKEY(F1);				 
					_NAT_CASE_KEY_TO_DIKEY(F2);					
					_NAT_CASE_KEY_TO_DIKEY(F3);					 
					_NAT_CASE_KEY_TO_DIKEY(F4);					
					_NAT_CASE_KEY_TO_DIKEY(F5);					
					_NAT_CASE_KEY_TO_DIKEY(F6);					
					_NAT_CASE_KEY_TO_DIKEY(F7);					 
					_NAT_CASE_KEY_TO_DIKEY(F8);					
					_NAT_CASE_KEY_TO_DIKEY(F9);					 
					_NAT_CASE_KEY_TO_DIKEY(F10);					
					_NAT_CASE_KEY_TO_DIKEY(F11);					 
					_NAT_CASE_KEY_TO_DIKEY(F12);					
					_NAT_CASE_KEY_TO_DIKEY(A);					 
					_NAT_CASE_KEY_TO_DIKEY(B);					
					_NAT_CASE_KEY_TO_DIKEY(C);					 
					_NAT_CASE_KEY_TO_DIKEY(D);					
					_NAT_CASE_KEY_TO_DIKEY(E);					
					_NAT_CASE_KEY_TO_DIKEY(F);					
					_NAT_CASE_KEY_TO_DIKEY(G);					 
					_NAT_CASE_KEY_TO_DIKEY(H);					
					_NAT_CASE_KEY_TO_DIKEY(I);					 
					_NAT_CASE_KEY_TO_DIKEY(J);					
					_NAT_CASE_KEY_TO_DIKEY(K);					 
					_NAT_CASE_KEY_TO_DIKEY(L);					
					_NAT_CASE_KEY_TO_DIKEY(M);					 
					_NAT_CASE_KEY_TO_DIKEY(N);					
					_NAT_CASE_KEY_TO_DIKEY(O);					 
					_NAT_CASE_KEY_TO_DIKEY(P);					
					_NAT_CASE_KEY_TO_DIKEY(Q);					
					_NAT_CASE_KEY_TO_DIKEY(R);					
					_NAT_CASE_KEY_TO_DIKEY(S);					 
					_NAT_CASE_KEY_TO_DIKEY(T);					
					_NAT_CASE_KEY_TO_DIKEY(U);					 
					_NAT_CASE_KEY_TO_DIKEY(V);					
					_NAT_CASE_KEY_TO_DIKEY(W);					 
					_NAT_CASE_KEY_TO_DIKEY(X);					
					_NAT_CASE_KEY_TO_DIKEY(Y);					 
					_NAT_CASE_KEY_TO_DIKEY(Z);					
					_NAT_CASE_KEY_TO_DIKEY(CapsLock);					 
					_NAT_CASE_KEY_TO_DIKEY(LeftAlt);					
					_NAT_CASE_KEY_TO_DIKEY(RightAlt);					
					_NAT_CASE_KEY_TO_DIKEY(LeftShift);					
					_NAT_CASE_KEY_TO_DIKEY(RightShift);					 
					_NAT_CASE_KEY_TO_DIKEY(LeftControl);					
					_NAT_CASE_KEY_TO_DIKEY(RightControl);					 
					_NAT_CASE_KEY_TO_DIKEY(LeftBracket);					
					_NAT_CASE_KEY_TO_DIKEY(RightBracket);					 
					_NAT_CASE_KEY_TO_DIKEY(LeftWindows);					
					_NAT_CASE_KEY_TO_DIKEY(RightWindows);					 
					_NAT_CASE_KEY_TO_DIKEY(Add);					
					_NAT_CASE_KEY_TO_DIKEY(Minus);					 
					_NAT_CASE_KEY_TO_DIKEY(Equals);					
					_NAT_CASE_KEY_TO_DIKEY(Insert);					
					_NAT_CASE_KEY_TO_DIKEY(Delete);					 
					_NAT_CASE_KEY_TO_DIKEY(Home);					
					_NAT_CASE_KEY_TO_DIKEY(End);					
					_NAT_CASE_KEY_TO_DIKEY(Power);					
					default:
						return NAT_DIK_None;
				}				 
			}
		}
	}
}
typedef ParadigmEngine::NativeInterface::Input::ENativeKeycode_DirectInput ENativeKeycode_DirectInput;

#endif