-- Hello World Lua declarative

ui:rectangle "root"
{
  x = -1.0;
  y = -1.0;
  width = 2.0;
  height = 2.0;
  gradient = ui:gradient
  {
    bottomLeft = glm:vec3(0.1, 0.1, 0.1);
    topLeft = glm:vec3(0.3, 0.3, 0.3);
    topRight= glm:vec3(0.6, 0.6, 0.6);
    bottomRight = glm:vec3(0.9, 0.9, 0.9);
  };

  ui:rectangle "modal"
  {
    x = -0.5;
    y = -0.5;
    width = 1.0;
    height = 1.0;

    color = glm:vec3(0.6, 0.6, 0.6);

    border = ui:border
    {
      color = glm:vec3(0.2, 0.2, 0.2);
      width = 0.02;
    };

    radius = ui:radius
    {
      radius = 0.1;
      topRight =0.5;
    };

    ui:rectangle "hideItem"
    {
      x = -0.9;
      y = -0.6;
      width = 1.8;
      height = 1.6;
      alpha = 0.0;

      text = ui:text
      {
        alignVerical = "center";
        alignHorizontal = "center";
        text = "'Hello world' from lua! :)\nMessageBox example...";
        height = 0.2;
        font = "DejaVuSans";
      };
    };

    ui:rectangle "button"
    {
      x = -0.9;
      y = -0.9;
      width = 1.8;
      height = 0.35;

      color = glm:vec3(0.4, 0.4, 0.4);

      border = ui:border
      {
        color = glm:vec3(0.2, 0.2, 0.2);
        width = 0.1;
      };

      radius = ui:radius
      {
        radius = 0.5;
      };

      text = ui:text
      {
        alignVerical = "center";
        alignHorizontal = "center";
        text = "Exit";
        height = 1;
        font = "DejaVuSans";
      };

      onPressed = function()
        print ("Pressed BUTTON")
        ui.button.border = ui:border
        {
          color = glm:vec3(0.9, 0.9, 0.9);
          width = 0.01;
        };
      end;

      onClick = function()
        print ("Clicked BUTTON!")
      end;

      onReleased = function()
        print ("Released BUTTON")
        ui.button.border = ui:border
        {
          color = glm:vec3(0.2, 0.2, 0.2);
          width = 0.01;
        };
      end;
      
    };
  };
}; -- rectangle "root"
