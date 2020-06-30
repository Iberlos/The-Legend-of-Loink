#pragma once

namespace GameDev2D
{
	class Timer
	{
	public: 
		Timer(double duration, bool doesLoop = false);
        Timer(const Timer& timer);
        Timer();

		void Update(double delta);

		void Start();
		void Stop();
		void Reset();

        void SetDuration(double aDuration);
        void SetDoesLoop(bool aDoesLoop);

		float GetPercentage();

        double GetElapsed();
        double GetDuration();

        bool IsRunning();
        bool DoesLoop();

	private:
		double m_Duration;
		double m_Elapsed;
		bool m_IsRunning;
        bool m_DoesLoop;
	};
}