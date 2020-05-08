#ifndef JGAMEBUTTON
#define JGAMEBUTTON

namespace J
{
	namespace GAME
	{
		enum ButtonState
		{
			StateNone=0,
			StateNormal,
			StateDisabled,
			StateHover,
			StatePressed,
			StateReleased
		};
		class JGameButton : public ::J::GAME::JGameElement
		{
		public:
			JGameButton();
			~JGameButton();

			virtual void Init(const std::string name, std::string applink, json button);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			virtual void		SetState(ButtonState state);
			const ButtonState	GetState() { return mState; }

			virtual void		InitButtonText();

			virtual void AddOnReleased(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function, json params);
			virtual void RemoveOnReleased(J::BASE::JBase* caller);

			virtual void AddOnHover(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function, json params);
			virtual void RemoveOnHover(J::BASE::JBase* caller);

			virtual void AddOnPressed(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function, json params);
			virtual void RemoveOnPressed(J::BASE::JBase* caller);

			virtual void AddOnLongPress(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function, json params);
			virtual void RemoveOnLongPress(J::BASE::JBase* caller);

			virtual bool CanBeOverriden() { return mCanBeOverriden; }
			virtual void SetTimeForLongPressed(__int64 time) { mTimeForLongPress = time; }
			virtual __int64 GetTimeForLongPressed() { return mTimeForLongPress; }

		protected:
			struct ButtonCallack
			{
				std::function<void(JGameButton*, json)>	Function;
				json									Params;
			};

			void	FillStatedElements();
			void	ReadChildsForState(ButtonState state, json childs);

			ButtonState		mState;
			json			mjsonStatedElements;

			std::map<JGameElement*, std::vector<ButtonState>> mStatedElements;

			//APPFUNCTIONS PART
			void AddCallback(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function,json params,
				std::map< J::BASE::JBase*, ButtonCallack>* map);
			void RemoveCallback(J::BASE::JBase* caller, std::map< J::BASE::JBase*, ButtonCallack>* map);

			std::map< J::BASE::JBase*, ButtonCallack> mOnReleased;
			std::map< J::BASE::JBase*, ButtonCallack> mOnHover;
			std::map< J::BASE::JBase*, ButtonCallack> mOnPressed;
			std::map< J::BASE::JBase*, ButtonCallack> mOnLongPress;

			bool			mCanBeOverriden;
			__int64			mTimeForLongPress;
			J::BASE::JTimer mLongPressTimer;

			virtual void	LongPressTimerCallback();
		};
	}
}

#endif