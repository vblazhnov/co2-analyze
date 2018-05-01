using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;

using vblazhnov.Co2.Service.Models;
using vblazhnov.Co2.Service.Services;

namespace vblazhnov.Co2.Service.Controllers
{
    [Route("api/[controller]")]
    public class SensorDataController : Controller
    {
        private ISensorDataService dataService;

        [HttpGet]
        public IActionResult Get([FromQuery] DateTime from, [FromQuery] DateTime to)
        {
            if (!Request.Query.ContainsKey("from") || !Request.Query.ContainsKey("to"))
            {
                return BadRequest();
            }
            return Json(this.dataService.Get(from, to));
        }

        [HttpPost]
        public IActionResult Post([FromBody]SensorData data)
        {
            if (data == null || !data.IsValid)
            {
                return BadRequest();
            }
            
            this.dataService.Add(data);
            return Ok();
        }

        public SensorDataController(ISensorDataService dataService)
        {
            this.dataService = dataService;
        }
    }
}
