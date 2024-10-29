import os
from gimpfu import *

def convert_images_format(image, drawable, folder_path, target_format):
    # Get all image files in the folder with a specific extension
    image_files = [f for f in os.listdir(folder_path) if f.endswith('.png')]
    
    if not image_files:
        pdb.gimp_message("No PNG images found in the folder.")
        return

    # Loop through each image and convert it to the target format
    for image_file in image_files:
        # Load the image
        full_path = os.path.join(folder_path, image_file)
        img = pdb.gimp_file_load(full_path, full_path)
        
        # Construct the new filename with the target extension
        base_name = os.path.splitext(image_file)[0]
        new_file_path = os.path.join(folder_path, base_name + '.' + target_format)

        # Save the image in the new format
        if target_format.lower() == "xpm":
            pdb.gimp_xpm_save(img, img.active_layer, new_file_path, new_file_path)
        else:
            pdb.gimp_file_save(img, img.active_layer, new_file_path, new_file_path)

        # Close the image to free memory
        pdb.gimp_image_delete(img)

    pdb.gimp_message(f"All images converted to {target_format} format in the folder.")

# Register the function in GIMP
register(
    "python_fu_convert_images_format",
    "Convert Images Format",
    "Converts all PNG images in a folder to the specified format.",
    "Your Name", "Your Name", "2023",
    "<Image>/File/Batch Processing/Convert Images Format...",
    "*",  # This script doesn't require an existing image open
    [
        (PF_DIRNAME, "folder_path", "Folder containing images", None),
        (PF_STRING, "target_format", "Target format (e.g., xpm)", "xpm")
    ],
    [],
    convert_images_format
)

main()
