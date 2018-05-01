using System;

using vblazhnov.Co2.Service.Models;

namespace vblazhnov.Co2.Service.Services
{
    public interface ISensorDataService
    {
        void Add(SensorData data);

        SensorData[] Get(DateTime from, DateTime to);
    }
}