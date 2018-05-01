
using System;
using System.Linq;

using MongoDB.Driver;

using vblazhnov.Co2.Service.Models;

namespace vblazhnov.Co2.Service.Services
{
    internal sealed class SensorDataService : ISensorDataService
    {
        private readonly IMongoCollection<SensorData> collection;

        public void Add(SensorData data)
        {
            this.collection.InsertOne(data);
        }

        public SensorData[] Get(DateTime from, DateTime to)
        {
            return this.collection
                .Find(d => d.Date >= from && d.Date <= to)
                .ToEnumerable()
                .ToArray();
        }

        public SensorDataService(IMongoCollection<SensorData> collection)
        {
            this.collection = collection;
        }
    }
}