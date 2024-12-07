import React from 'react';

const TourSchedule = () => {
  const days = [
    { day: 'Sat', date: 20, bgColor: '#D4E6F1', borderColor: '#2E86C1' },
    { day: 'Sun', date: 21, bgColor: '#FCF3CF', borderColor: '#F4D03F' },
    { day: 'Mon', date: 22, bgColor: '#FADBD8', borderColor: '#E74C3C' },
    { day: 'Tue', date: 23, bgColor: '#D5F5E3', borderColor: '#27AE60' }
  ];

  const schedules = [
    {
      day: 1,
      title: 'Journey Begins',
      bgColor: '#D4E6F1',
      borderColor: '#2E86C1',
      events: [
        { time: '10:00 AM', event: 'Departure from Dhaka' },
        { time: '08:00 PM', event: 'Arrival at Hotel Sea Crown' }
      ]
    },
    {
      day: 2,
      title: 'Beach Paradise',
      bgColor: '#FCF3CF',
      borderColor: '#F4D03F',
      events: [
        { time: '06:00 AM', event: 'Sunrise at Marine Drive' },
        { time: '02:00 PM', event: 'Inani Beach Visit' },
        { time: '08:00 PM', event: 'Seafood Dinner at Handi' }
      ]
    },
    {
      day: 3,
      title: 'Adventure Day',
      bgColor: '#FADBD8',
      borderColor: '#E74C3C',
      events: [
        { time: '11:00 AM', event: 'Himchori Waterfall' },
        { time: '04:00 PM', event: 'Buddhist Temple Visit' },
        { time: '07:00 PM', event: 'Beach Bonfire & BBQ' }
      ]
    },
    {
      day: 4,
      title: 'Farewell',
      bgColor: '#D5F5E3',
      borderColor: '#27AE60',
      events: [
        { time: '10:00 AM', event: 'Souvenir Shopping' },
        { time: '02:00 PM', event: 'Return Journey Begins' }
      ]
    }
  ];

  return (
    <div className="w-[608px] h-[705px] bg-white rounded-[50px] relative p-8">
      <div className="text-3xl font-bold text-[#003049] mb-6 bg-[rgba(0,48,73,0.1)] p-4 rounded-xl shadow-lg inline-block">
        Seaside Serenity: Cox's Bazar Adventure
      </div>

      <div className="mb-6">
        <div className="text-[#525050] text-base mb-2">4 Days Adventure</div>
        <div className="text-[#151313] text-xl font-medium">Starting Saturday, 20 November 2024</div>
      </div>

      <div className="flex gap-4 mb-8">
        {days.map(({ day, date, bgColor }, i) => (
          <div 
            key={i} 
            className="w-16 h-[72px] rounded-[18px] flex flex-col items-center justify-center text-gray-700 shadow-lg hover:scale-105 transition-transform"
            style={{ backgroundColor: bgColor }}
          >
            <span className="text-sm font-medium">{day}</span>
            <span className="text-lg font-bold">{date}</span>
          </div>
        ))}
      </div>

      <div className="relative space-y-4 overflow-auto h-[450px] pr-4">
        {schedules.map((schedule, index) => (
          <div 
            key={index}
            className="p-6 rounded-xl shadow-lg hover:scale-[1.02] transition-transform"
            style={{ 
              backgroundColor: schedule.bgColor,
              borderLeft: `8px solid ${schedule.borderColor}`
            }}
          >
            <div className="font-bold mb-2" style={{ color: schedule.borderColor }}>
              Day {schedule.day} - {schedule.title}
            </div>
            <div className="space-y-2">
              {schedule.events.map((event, i) => (
                <div key={i} className="flex items-center">
                  <span className="text-[#1E1D1D] font-medium w-24">{event.time}</span>
                  <span>{event.event}</span>
                </div>
              ))}
            </div>
          </div>
        ))}
      </div>

      <div className="absolute bottom-0 left-0 right-0 h-24 bg-gradient-to-t from-white to-transparent pointer-events-none" />
    </div>
  );
};

export default TourSchedule;