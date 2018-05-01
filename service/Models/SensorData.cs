
using System;
using MongoDB.Bson.Serialization.Attributes;
using Newtonsoft.Json;

namespace vblazhnov.Co2.Service.Models
{
    [BsonIgnoreExtraElements]
    public sealed class SensorData
    {
        [JsonIgnore]
        public UInt16 MaximalCo2Concentration = 5000;
        public DateTime Date { get; set; }
        public UInt16 Co2 { get; set; }

        [JsonIgnore]
        public bool IsValid
        {
            get
            {
                return this.Date != default(DateTime) && Co2 <= MaximalCo2Concentration;
            }
        }
    }
}